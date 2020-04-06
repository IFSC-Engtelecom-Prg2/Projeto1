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

    // calcula a variação desta cotação em relação a uma cotação anterior
    double variacao(const Cotacao & ant) const;
};

// Um ativo financeiro
class Ativo {
public:
    Ativo(const string & nome);
    Ativo();

    string get_nome() const { return nome;}

    // calcula retorno financeiro entre primeira e última cotações deste ativo
    double retorno() ;

    // calcula volatilidade entre primeira e última cotações deste ativo
    double volatilidade() ;

    // calcula índice de sharpe entre primeira e última cotações deste ativo
    // necessita um ativo de referência
    double sharpe(Ativo & ref) ;

    // adiciona uma cotação à lista de cotações deste ativo
    void adiciona_cotacao(const Cotacao & cot);

    // obtém este ativo com cotações contidas no período indicado
    Ativo por_periodo(const string & data1, const string & data2);
    Ativo por_periodo(int data1, int data2);

    // converte data no formato "mes/ano" para um inteiro (contagem de meses desde AnoRef)
    static int data2int(const string & data);

    // Cria um ativo a partir de uma linha com formato: "data nome_ativo cotação"
    static Ativo cria(const string & linha);

    // ordena cotações por data
    void ordena();

    bool operator==(const Ativo & o) const;

    // Adiciona as cotações de outro ativo para este ativo
    void adiciona(const Ativo & ativo);
private:
    string nome; // o código de negociação do ativo
    list<Cotacao> cotacoes;// a lista de cotações deste ativo
    bool sorted;

    // busca a cotaçao de uma data específica
    Cotacao & obtem_cotacao(int data);
};

// um resultado de uma análise
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
    // construtor: inicia o analisador, carregando os dados do arquivo nomearq
    Analisador(const string & nomearq);

    // gera os N resultados entre data1 e data2
    list<Resultado> retornos(int N, const string &data1, const string & data2);
    list<Resultado> volatilidades(int N, const string &data1, const string & data2);
    list<Resultado> sharpe(int N, const string &data1, const string & data2);

    // retorna true se não houver ativos carregados
    bool empty()const { return ativos.empty();}
private:
    list<Ativo> ativos;

    // atualiza um ativo a partir do conteúdo do parâmetro "ativo"
    // se não possuir ainda esse ativo, adiciona-o à lista de ativos
    void atualiza(Ativo & ativo);

    // procura um ativo por seu nome
    Ativo & procura(const string & nome);

    // gera uma lista com os N primeiros valores de r
    list<Resultado> extraiN(list<Resultado> & r, int N);
};

#endif //PROJETO1_ANALISADOR_H
