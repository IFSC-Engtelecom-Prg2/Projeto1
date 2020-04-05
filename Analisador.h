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

struct Cotacao {
    int data; // a data representada como a quantidade de meses desde jan/1980
    float valor; // o valor do ativo
};

struct Ativo {
    string nome; // o código de negociação do ativo
    list<Cotacao> cotacoes;// a lista de cotações deste ativo
};

struct Resultado {
    string nome; // o código de negociação do ativo
    float info; // o valor do resuatdo (ex: retorno, volatilidade, sharpe)
};

// lê o arquivo de dados, transformando-os em uma lista de Ativos com suas cotações
void an_le_dados(const string & nomearq, list<Ativo> & result);

// Calcula o retorno financeiro de cada ativo da lista "dados"
list<Resultado> an_retornos(list<Ativo> & dados, const string & data1, const string & data2);

// Calcula a volatilidade de cada ativo da lista "dados"
list<Resultado> an_volatilidades(list<Ativo> & dados, const string & data1, const string & data2);

// Calcula o índice de Sharpe de cada ativo da lista "dados"
list<Resultado> an_sharpe(list<Ativo> & dados, const string & data1, const string & data2);

// operador < (menor que) para comparar dois valores do tipo Resultado
bool operator<(const Resultado & r1, const Resultado & r2);

#endif //PROJETO1_ANALISADOR_H
