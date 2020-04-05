//
// Created by sobral on 05/04/2020.
//

#ifndef PROJETO1_UTEIS_H
#define PROJETO1_UTEIS_H

#include <vector>
#include <list>
#include <string>

using std::string;
using std::vector;
using std::list;

// funções de uso geral ...

// separa uma string em substrings, usando "sep" como delimitador
vector<string> separa(string algo, char sep=' ');

// calcula a média de um conjunto de números
double stddev(const list<double> & val);

// calcula o desvio padrão de um conjunto de números
double media(const list<double> & val);

#endif //PROJETO1_UTEIS_H
