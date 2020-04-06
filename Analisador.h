//
// Created by sobral on 05/04/2020.
//

#ifndef PROJETO1_ANALISADOR_H
#define PROJETO1_ANALISADOR_H

#include <list>
#include <string>

using std::list;
using std::string;

const int ANO_REF = 1980;

// Tipos de dados do analisador
struct Cotacao {
    int data; // a data representada como a quantidade de meses desde jan/1980
    float valor; // o valor do ativo

    Cotacao() {}
    Cotacao(int date, float val):data(date), valor(val) {}
    bool operator<(const Cotacao & cot) const;
    double variacao(const Cotacao & ant) const;
};

class Ativo {
public:
    Ativo(const string & nome);
    Ativo();

    string get_nome() const { return nome;}
    double retorno() ;
    double volatilidade() ;
    double sharpe(Ativo & ref) ;

    void adiciona_cotacao(const Cotacao & cot);
    Ativo por_periodo(const string & data1, const string & data2);
    Ativo por_periodo(int data1, int data2);

    static int data2int(const string & data);
    static Ativo cria(const string & linha);
    void ordena();

    bool operator==(const Ativo & o) const;
    void adiciona(const Ativo & ativo);
private:
    string nome; // o código de negociação do ativo
    list<Cotacao> cotacoes;// a lista de cotações deste ativo
    bool sorted;

    Cotacao & obtem_cotacao(int data);
};

struct Resultado {
    string nome; // o código de negociação do ativo
    float info; // o valor do resultado (ex: retorno, volatilidade, sharpe)

    Resultado() {}
    Resultado(const string & name):nome(name) {}
    Resultado(const string & name, float val):nome(name), info(val) {}
    bool operator<(const Resultado & r) const;
};

class Analisador {
public:
    Analisador(const string & nomearq);

    list<Resultado> retornos(int N, const string &data1, const string & data2);
    list<Resultado> volatilidades(int N, const string &data1, const string & data2);
    list<Resultado> sharpe(int N, const string &data1, const string & data2);

    bool empty()const { return ativos.empty();}
private:
    list<Ativo> ativos;

    void atualiza(Ativo & ativo);
    Ativo & procura(const string & nome);
    list<Resultado> extraiN(list<Resultado> & r, int N);
};

#endif //PROJETO1_ANALISADOR_H
