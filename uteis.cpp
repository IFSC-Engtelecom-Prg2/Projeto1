//
// Created by sobral on 05/04/2020.
//

#include "uteis.h"
#include <math.h>

double media(const list<double> & val) {
    double m=0;

    if (val.empty()) return 0;
    for (auto & x: val) m += x;
    return m/val.size();
}

double stddev(const list<double> & val) {
    double s=0, m=media(val);

    if (m == 0) return 0;
    for (auto & x: val) s += (x-m)*(x-m);
    return sqrt(s/val.size());
}

vector<string> separa(string algo, char sep) {
    // implemente aqui sua função ...
    int pos=0; // posição do primeiro caractere da palavra atual
    vector<string> q;

    while (pos != string::npos) {
        // procura primeiro caractere diferente do separador
        int pos1 = algo.find_first_not_of(sep, pos);

        // se não encontrou, sai do laço
        if (pos1 == string::npos) break;

        // agora procura o próximo caractere separador a partir da posição anterior
        pos = algo.find(sep, pos1);

        int len; // comprimento da palavra identificada

        // se há próximo separador, calcula o comprimento
        if (pos != string::npos) len = pos - pos1;
        else len = pos; //senão, em vez de comprimento use o valor string::npos

        // copia a palavra e a enfileira
        string s = algo.substr(pos1, len);
        q.push_back(s);
    }

    return q;
}