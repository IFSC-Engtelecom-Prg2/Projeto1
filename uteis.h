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

vector<string> separa(string algo, char sep=' ');
double stddev(const list<double> & val);
double media(const list<double> & val);

#endif //PROJETO1_UTEIS_H
