//
// Created by sobral on 05/04/2020.
//
#include "Analisador.h"
#include "uteis.h"
#include <fstream>
#include <map>
#include <math.h>

using std::ifstream;
using std::pair;
using std::stof;
using std::stoi;

typedef pair<string,Cotacao> CotacaoAtivo;

int converte_data(const string & data) {
    int mes, ano;
    auto par = separa(data, '/');

    if (par.size() != 2) return 0; // erro ! data com formato errado
    mes = stoi(par[0]);
    ano = stoi(par[1]);

    return (ano - ANO_REF)*12 + mes;
}

Ativo& obtem_ativo(list<Ativo> & dados, const string & nome) {
    for (auto &ativo: dados) {
        if (ativo.nome == nome) return ativo;
    }

    throw -1;
}


CotacaoAtivo gera_cotacao(const string & linha) {
    auto itens = separa(linha);
    if (itens.size() != 3) throw -1; // erro !!

    Cotacao cot;

    cot.valor = stof(itens[2]);
    cot.data = converte_data(itens[0]);

    return CotacaoAtivo(itens[1], cot);
}

void adiciona_cotacao(list<Ativo> & dados, const string & nome_ativo, const Cotacao & cot) {
    try {
        auto & ativo = obtem_ativo(dados, nome_ativo);
        ativo.cotacoes.push_back(cot);
    } catch (...) {
        Ativo ativo;
        ativo.nome = nome_ativo;
        ativo.cotacoes.push_back(cot);
        dados.push_back(ativo);
    }
}

Cotacao obtem_cotacao(Ativo & ativo, int data) {
    for (auto & cot: ativo.cotacoes) {
        if (cot.data == data) return cot;
    }

    throw -1; // sem cotação para essa data !
}

Resultado retorno_financeiro(Ativo & ativo, int data1, int data2) {
    auto cot1 = obtem_cotacao(ativo, data1);
    auto cot2 = obtem_cotacao(ativo, data2);

    Resultado r;

    r.nome = ativo.nome;
    r.info = (cot2.valor - cot1.valor)/cot1.valor;
    return r;
}

Resultado volatilidade(Ativo & ativo, int data1, int data2) {
    list<double> l_cot;

    for (int data=data1; data <= data2; data++) {
        auto cot = obtem_cotacao(ativo, data);
        l_cot.push_back(cot.valor);
    }

    Resultado r;

    r.nome = ativo.nome;
    r.info = stddev(l_cot);

    return r;
}

Resultado sharpe(Ativo & ativo, double ref, int data1, int data2) {
    auto ret = retorno_financeiro(ativo, data1, data2);
    auto vol = volatilidade(ativo, data1, data2);

    Resultado r;
    r.info = (ret.info - ref)/vol.info;
    r.nome = ativo.nome;

    return r;
}

void an_le_dados(const string &nomearq, list<Ativo> &result) {
    ifstream arq(nomearq);

    if (! arq.is_open()) return; // nada pode ser lido ... não conseguiu abrir o arquivo

    string linha;
    while (getline(arq, linha)) {
        try {
            auto cot = gera_cotacao(linha);
            adiciona_cotacao(result, cot.first, cot.second);
        } catch (...) {
            // ignora ...
        }
    }
}

list<Resultado> an_retornos(list<Ativo> &dados, const string & data1, const string & data2) {
    auto d1 = converte_data(data1);
    auto d2 = converte_data(data2);
    list<Resultado> res;

    for (auto & ativo: dados) {
        try {
            res.push_back(retorno_financeiro(ativo, d1, d2));
        } catch(...) {
            // ignora .. sem cotação em ao menos uma das datas
        }
    }
    return res;
}

list<Resultado> an_volatilidades(list<Ativo> &dados, const string & data1, const string & data2) {
    auto d1 = converte_data(data1);
    auto d2 = converte_data(data2);
    list<Resultado> res;

    for (auto & ativo: dados) {
        try {
            res.push_back(volatilidade(ativo, d1, d2));
        } catch(...) {
            // ignora .. sem cotação em ao menos uma das datas
        }
    }
    return res;
}

list<Resultado> an_sharpe(list<Ativo> &dados, const string & data1, const string & data2) {
    list<Resultado> res;
    auto d1 = converte_data(data1);
    auto d2 = converte_data(data2);
    auto &lft = obtem_ativo(dados, "LFT");
    auto ref = retorno_financeiro(lft, d1, d2);

    for (auto & ativo: dados) {
        try {
            res.push_back(sharpe(ativo, ref.info, d1, d2));
        } catch(...) {
            // ignora .. sem cotação em ao menos uma das datas
        }
    }
    return res;
}

bool operator<(const Resultado &r1, const Resultado &r2) {
    if (r1.info == r2.info) return r1.nome < r2.nome;
    return r1.info < r2.info;
}
