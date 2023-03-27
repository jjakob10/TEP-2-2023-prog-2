// Definição do Ponteiro para o tipo tPredicao
typedef struct tPredicao_st *tPredicao_pt;

#ifndef _TPROPRED_H_
#define _TPROPRED_H_
#include "tLista.h"
#include "tPalavra.h"
#include "utils.h"

// Aloca e retorna um novo tPredicao
tPredicao_pt NovaPredicao(int idx, char *real, char *predita);

// Retorna verdadeiro se a predição condiz com o esperado
int PredicaoCerta(tPredicao_pt pred);

// Retorna o valor armazenado real da classe a partir de um tPredicao passado como tipo void*
char *VoidPredReal(void* pred);

// Retorna o valor armazenado predito da classe a partir de um tPredicao passado como tipo void*
char *VoidPredPredita(void *pred);

// Retorna o valor armazenado real da classe
char *PredReal(tPredicao_pt pred);

// Retorna o valor armazenado predito da classe
char *PredPredita(tPredicao_pt pred);

// Compara os valores reais (prioridade maior), e então os valores preditos (strcmp)
int CompRealPred(const void *i1, const void *i2);

// Compara duas predições com strcmp
int CompPred(const void *i1, const void *i2);

// Compara duas classes reais com strcmp
int CompReal(const void *i1, const void *i2);

// Libera um tPredicao da memória
void LiberaPredicao(void *prd);

#endif