#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include "Analisador.h"

using namespace std;

// A interface de usuário foi implementada diretamente aqui em main.cpp

// o arquivo com os dados sobre cotações de ativos
const string ArqDados = "../data/dados.txt";

// apresenta o meu primcipal, e lê uma opção digitada pelo usuário
// retorna o número da opção escolhida
int menu_principal() {
    int op;

    cout << "1. Mostra N ativos com maior retorno em um período" << endl;
    cout << "2. Mostra N ativos com menor volatilidade em um período" << endl;
    cout << "3. Mostra N ativos com melhor índice de Sharpe em um período" << endl;
    cout << "4. Sai do programa" << endl;
    cout << "Opção: ";
    cin >> op;
    cin.ignore();

    return op;
}

// Lê dados complementares para a operação escolhida
// N: quantidade de resultados a serem apresentados
// d1: data inicial da análise (na forma mês/ano)
// d2: data final da análise
void menu_extra(int & N, string & d1, string & d2) {
    cout << "Número de resultados: ";
    cin >> N;
    cin.ignore();
    cout << "Data inicial (mês/ano): ";
    getline(cin, d1);
    cout << "Data final (mês/ano): ";
    getline(cin, d2);
}

// copia os N primeiros resultados existentes em "result"
// retorna uma nova lista com esses N valores
list<Resultado> extraiN_resultados(list<Resultado> & result, int N) {
    N = min<int>(N, result.size());
    list<Resultado> r(N);
    copy_n(result.begin(), N, r.begin());

    return r;
}

// Apresenta o resultado de uma análise
// N: quantidade de resultados a mostrar
void apresenta_resultado(list<Resultado> & res, int N) {
    auto r = extraiN_resultados(res, N);

    cout << "Resultado:" << endl;
    cout << "==========" << endl;
    for (auto & dado: r) {
        cout << dado.nome << " " << dado.info << endl;
    }
    cout << endl;
}

int main(int argc, char * argv[]) {
    // nesta lista ficarão os dados lidos do arquivos
    list<Ativo> dados;

    // lê os dados do arquivo de dados, convertendo-os para uma lista de Ativo
    an_le_dados(ArqDados, dados);

    // se nada conseguiu ler, termina a execução
    if (dados.empty()) {
        cout << "Erro: nenhum dado lido !" << endl;
        return 0;
    }

    // Laço principal: mostra o menu, lê a opção, e executa análise pedida
    int op;
    while ((op = menu_principal()) != 4) {
        int N;
        string data1, data2;

        // lê parâmetros da análise
        menu_extra(N, data1, data2);
        if (N <= 0) {
            cout << "Número de resultados inválido: deve ser > 0" << endl;
            continue;
        }

        switch (op) {
            case 1: { // retorno financeiro
                auto r = an_retornos(dados, data1, data2);
                r.sort();
                r.reverse();
                apresenta_resultado(r, N);
                break;
            }
            case 2: { // volatilidade
                auto r = an_volatilidades(dados, data1, data2);
                r.sort();
                apresenta_resultado(r, N);
                break;
            }
            case 3: { // índice de sharpe
                auto r = an_sharpe(dados, data1, data2);
                r.sort();
                r.reverse();
                apresenta_resultado(r, N);
                break;
            }
            default: {
                cout << "Opção " << op << " inválida" << endl;
                break;
            }
        }
    }

    return 0;
}