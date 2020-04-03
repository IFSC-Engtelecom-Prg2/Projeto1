# Objetivo

O programa a ser criado tem por objetivo **analisar ativos financeiros da Bolsa de Valores de São Paulo**, para identificar os 
ativos com melhor razão entre retorno e risco. 

# Resumo

As cotações dos ativos negociados na Bolsa de Valores de São Paulo (Bovespa) são mantidas em séries históricas. Com base
na análise dessas séries, informações relevantes para um investidor podem ser obtidas. Dentre elas, o retorno financeiro, a 
volatilidade e o índice de Sharpe em um determinado período. Com essas informações em mãos, um investidaor pode fazer melhor
escolhas de investimento, de forma a aumentar o ganho esperado e reduzir o risco.

Algumas informações são apresentadas a seguir para esclarecer os elementos da análise a ser realizada.

## Retorno financeiro

O retorno financeiro é definido como a porcentagem que expressa o aumento no valor de um ativo em um determinado período. Por exemplo, se em 1/1/2018 um ativo valia R$ 10,00, e em 1/7/2018 esse mesmo ativo vale R$ 12,10, então o retorno financeiro nesse período foi de 21%. De forma geral, o retorno de um ativo pode ser calculado assim:

```
Y = (Vf - Vi) / Vi x 100%
```

... sendo _Y_ o retorno financeiro, _Vf_ o valor no final do período analisado e _Vi_ o valor no início desse período.

## Volatilidade

A volatilidade é calculada como o desvio padrão das rentabilidades em um determinado período. A rentabilidade é dada pelo 
retorno financeiro em intervalos definidos (ex: diária, semanal, mensal, anual, ...). Por exemplo, seja a rentabilidade 
mensal de um certo ativo no ano de 2017:

**Mês** 	**Rentabilidade (em %)**
Jan 	0.42
Fev 	0.40
Mar 	0.53
Abr 	0.47
Mai 	0.55
Jun 	0.51
Jul 	0.32
Ago 	0.53
Set 	0.60
Out 	0.41
Nov 	0.59
Dez 	0.48

O desvio padrão dessas rentabilidades é calculado usando a fórmula para desvio padrão populacional, dada por:

s=

... sendo _xi_ um valor do conjunto, a média dos valores desse conjunto, e _n_ o tamanho do conjunto. Para o exemplo, a 
média é:

=0.484

... e o desvio padrão:

s = 0.08

## Índice de Sharpe

O índice de Sharpe relaciona o retorno financeiro de um ativo em um determinado período ao seu risco, comparado à rentabilidade de um ativo sem risco. O risco, no caso, é dado pela volatilidade da rentabilidade do ativo ao longo do período investigado. O índice de Sharpe pode ser calculado com esta expressão:

```
I = (Ri-R0)/Vi
```

... sendo _Ri_ o retorno do ativo _i_, _Vi_ a volatilidade desse ativo, e _R0_ o retorno de um ativo sem risco.

No Brasil costuma-se usar o título público LFT como referência para ativo sem risco. O LFT acompanha a taxa Selic 
definida pelo Banco Central.

**Referências**:
* [Estatísticas sobre Tesouro Direto](http://www.tesouro.gov.br/-/balanco-e-estatisticas)
* [Séries históricas de ativos negociados na Bovespa](http://www.b3.com.br/pt_br/market-data-e-indices/servicos-de-dados/market-data/historico/mercado-a-vista/series-historicas/)
* [Informações sobre as cotações históricas na Bovespa](http://www.b3.com.br/pt_br/market-data-e-indices/servicos-de-dados/market-data/historico/mercado-a-vista/cotacoes-historicas/)

# Modelagem

## Requisitos funcionais

Os requisitos funcionais do programa são:
* O programa deve ser capaz de apresentar os N ativos com maior retorno financeiro em um determinado período
* O programa deve ser capaz de apresentar os N ativos com menor volatilidade em um determinado período
* O programa deve ser capaz de apresentar os N ativos com melhor índice de Sharpe em um determinado período
* O programa deve ser capaz de fazer múltiplas análises sucessivas, até que o usuário opte por terminar sua execução

## Estrutura do programa

O programa será composto por dois blocos funcionais:
* **Interface de usuário**: a interface será orientada a menu. A _interface de usuário_ usa o _analisador de ativos_.
* **Analisador de ativos**: este bloco é responsável por efetuar as análises sobre séries temporais de cotações de ativos

## Representação dos dados

O programa usa três tipos de dados necessários para as análises:
* **Cotação**: uma cotação possui uma data e um valor
* **Ativo**: um ativo possui um nome e uma lista de cotações ordenada pela data
* **Resultado**: representa um resultado de uma análise de um ativo

As declarações desses tipos são estas:

```c++
struct Cotacao {
  int data; // a data representada como a quantidade de meses desde jan/1980
  float valor; // o valor do ativo
};

struct Ativo {
  string nome; // o código de negociação do ativo
  list<Cotacao> // a lista de cotações deste ativo
};

struct Resultado {
  string nome; // o código de negociação do ativo
  float info; // o valor do resuatdo (ex: retorno, volatilidade, sharpe)
};  
```

## Dados de entrada

A análise deve ser feita com base em um arquivo de dados com este formato:

```
mes/ano nome_do_ativo valor_em_R$
```

Ex:

```
01/2007 ALLL3 8.0
01/2007 ALLL4 3.68
```

Seu programa deve receber do usuário estas informações:
* Período de análise, na forma de um mês  e ano inicial, e mês e ano final (ex: 01/2018 a 08/2018)
* O tipo de análise a ser realizada
* A quantidade de ativos cujos resultados devem ser apresentados (parâmetro N)

## Dados de saída

O programa deve apresentar como resultado os dados da análise pedida pelo usuário. Esse resultado deve ser mostrado na tela.

# Funcionalidades do programa

As funcionalidades do programa são estas:

**Leitura do arquivo de dados**
* _Parâmetro de entrada_: caminho do arquivo
* _Resultado_: lista de ativos
* _Ações_:
  1. Cria uma lista de _Ativos_
  1. Abre o arquivo
  1. Para cada linha lida
     1. Transforma os dados da linha em uma cotação
     1. Localiza o ativo lido na lista de Ativos, e adiciona a ele a cotação lida
  1. Retorna a lista de ativos
    
**Análise de retorno financeiro**
* _Parâmetros de entrada_: lista de ativos, data inicial, data final, N
* _Resultado_: lista de Resultado
* _Ações_:
  1. Para cada ativo
     1. Calcula seu retorno financeiro no período
     1. Armazena o resultado na lista de resultados
  1. Ordena a lista de resultados
  1. Retorna os N últimos valores da lista de resultados
  
