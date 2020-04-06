//
// Created by sobral on 05/04/2020.
//
#include "Analisador.h"
#include "uteis.h"
#include <fstream>
#include <map>
#include <algorithm>

using std::ifstream;
using std::pair;
using std::stof;
using std::stoi;

bool Cotacao::operator<(const Cotacao &cot) const {
    return data < cot.data;
}

double Cotacao::variacao(const Cotacao &ant) const {
    return (valor - ant.valor)/ant.valor;
}

Ativo::Ativo(const string &nome): nome(nome), sorted(false) {
}

Ativo::Ativo(): sorted(false) {}

Ativo Ativo::cria(const string &linha) {
    auto itens = separa(linha);
    if (itens.size() != 3) throw -1; // erro !!

    Cotacao cot;

    cot.valor = stof(itens[2]);
    cot.data = data2int(itens[0]);

    Ativo ativo(itens[1]);
    ativo.adiciona_cotacao(cot);
    return ativo;
}

bool Ativo::operator==(const Ativo &o) const {
    return nome == o.nome;
}

void Ativo::adiciona_cotacao(const Cotacao &cot) {
    cotacoes.push_back(cot);
    sorted = false;
}

void Ativo::ordena() {
    if (not sorted) {
        sorted = true;
        cotacoes.sort();
    }
}

Ativo Ativo::por_periodo(int data1, int data2) {
    Ativo res(nome);

    for (auto & cot: cotacoes) {
        if (cot.data <= data1 and cot.data >= data2) res.adiciona_cotacao(cot);
    }

    res.ordena();
    return res;
}

Ativo Ativo::por_periodo(const string &data1, const string &data2) {
    return por_periodo(data2int(data1), data2int(data2));
}

int Ativo::data2int(const string &data) {
    int mes, ano;
    auto par = separa(data, '/');

    if (par.size() != 2) return 0; // erro ! data com formato errado
    mes = stoi(par[0]);
    ano = stoi(par[1]);

    return (ano - ANO_REF)*12 + mes;
}

Cotacao& Ativo::obtem_cotacao(int data) {
    for (auto & cot: cotacoes) {
        if (cot.data == data) return cot;
    }
    throw -1;
}

double Ativo::retorno() {
    if (not sorted) ordena();
    auto cot1 = cotacoes.front();
    auto cot2 = cotacoes.back();

    if (cot1.valor == 0) throw -1;
    return cot2.variacao(cot1);
}

double Ativo::volatilidade() {
    if (not sorted) ordena();

    list<double> l_var;
    auto it = cotacoes.begin();
    auto cot1 = *it;

    for (it++; it != cotacoes.end(); it++) {
        l_var.push_back(it->variacao(cot1));
        cot1 = *it;
    }

    return stddev(l_var);
}

double Ativo::sharpe(Ativo & ref) {
    return (retorno() - ref.retorno())/volatilidade();
}

void Ativo::adiciona(const Ativo &ativo) {
    for (auto & cot: ativo.cotacoes) cotacoes.push_back(cot);
    sorted = false;
}

/**********************************************************
 Funções públicas deste módulo ... API do analisador
**********************************************************/

Analisador::Analisador(const string &nomearq) {
    ifstream arq(nomearq);

    if (! arq.is_open()) return; // nada pode ser lido ... não conseguiu abrir o arquivo

    string linha;
    while (getline(arq, linha)) {
        try {
            auto ativo = Ativo::cria(linha);
            atualiza(ativo);
        } catch (...) {
            // ignora ...
        }
    }
}

void Analisador::atualiza(Ativo &ativo) {
    try {
        auto & asset = procura(ativo.get_nome());
        asset.adiciona(ativo);
    } catch (...) {
        ativos.push_back(ativo);
    }
}

list<Resultado> Analisador::extraiN(list<Resultado> &r, int N) {
    N = std::min<int>(N, r.size());
    list<Resultado> res(N);
    std::copy_n(r.begin(), N, res.begin());

    return res;
}

list<Resultado> Analisador::retornos(int N, const string &data1, const string &data2) {
    list<Resultado> res;
    int d1 = Ativo::data2int(data1);
    int d2 = Ativo::data2int(data2);

    for (auto & ativo:ativos) {
        auto novo = ativo.por_periodo(d1, d2);

        try {
            Resultado r(novo.get_nome(), novo.retorno());
            res.push_back(r);
        } catch(...) {}
    }

    res.sort();
    res.reverse();
    return extraiN(res, N);
}

list<Resultado> Analisador::volatilidades(int N, const string &data1, const string &data2) {
    list<Resultado> res;
    int d1 = Ativo::data2int(data1);
    int d2 = Ativo::data2int(data2);

    for (auto & ativo: ativos) {
        try {
            auto novo = ativo.por_periodo(d1, d2);
            Resultado r(novo.get_nome(), novo.retorno());
            if (r.info != 0) res.push_back(r);
        } catch(...) {
            // ignora .. sem cotação em ao menos uma das datas
        }
    }
    res.sort();
    return extraiN(res, N);
}

Ativo& Analisador::procura(const string &nome) {
    for (auto & ativo: ativos) {
        if (ativo.get_nome() == nome) return ativo;
    }

    throw -1;
}

list<Resultado> Analisador::sharpe(int N, const string &data1, const string &data2) {
    list<Resultado> res;
    int d1 = Ativo::data2int(data1);
    int d2 = Ativo::data2int(data2);
    auto &lft = procura("LFT");
    auto ref = lft.por_periodo(d1, d2);

    for (auto & ativo: ativos) {
        try {
            auto novo = ativo.por_periodo(d1, d2);
            Resultado r(novo.get_nome(), novo.sharpe(ref));
        } catch(...) {
            // ignora .. sem cotação em ao menos uma das datas
        }
    }
    res.sort();
    res.reverse();
    return extraiN(res, N);
}

bool Resultado::operator<(const Resultado &r) const {
    if (info == r.info) return nome < r.nome;
    return info < r.info;
}
