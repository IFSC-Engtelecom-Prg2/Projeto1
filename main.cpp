#include <iostream>
#include <list>

using namespace std;

int conta(list<string> & l, const string & algo) {
    int n = 0;

    for (auto & x: l) if (x == algo) n++;

    return n;
}

int main() {
    list<string> coisas;

    coisas.push_back("abc");
    coisas.push_back("xyz");
    coisas.push_back("mamão");
    coisas.push_back("tainha");
    coisas.push_back("abc");

    for (auto & treco: coisas) {
        cout << treco << ": " << conta(coisas, treco) << endl;
    }
    return 0;
}