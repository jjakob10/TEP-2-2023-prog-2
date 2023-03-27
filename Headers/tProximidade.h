// Definição do Ponteiro para o tipo tProximidade
typedef struct tProximidade_st *tProximidade_pt;

#ifndef _TPROPROX_H_
#define _TPROPROX_H_
#include "tLista.h"
#include "utils.h"
#include "tPalavra.h"

// Aloca e retorna um novo tProximidade
tProximidade_pt NovaProximidade(int idx, double prox);

// Retorna o valor de index de um tProximidade
int ProxIdx(tProximidade_pt px) ;

// Retorna o valor de proximidade de um tProximidade
double ProxProx(tProximidade_pt px);

// Comprara o valor de proximidade de dois tProximidade
int CompProx(const void *i1, const void *i2) ;

// Libera um tProximidade da memória
void LiberaProx(void *px);

#endif