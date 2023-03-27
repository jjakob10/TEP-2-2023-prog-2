#ifndef _TPROPRIEDADEPAL_H_
#define _TPROPRIEDADEPAL_H_
#include "tLista.h"
#include "utils.h"
#include "tPalavra.h"

// Definição do Ponteiro para o tipo tPropriedadePal
typedef struct tPropriedadePal_st *tPropriedadePal_pt;

// Aloca e retorna uma nova tPropriedadePal, mas retorna esse como um void*
void *NovaVoidPropPal(char *pal, int freq);

// Aloca e retorna uma nova tPropriedadePal
tPropriedadePal_pt NovaPropPal(char *, int);

// Retorna a palavra armazenada em tPropriedadePal, mas recebe esse como um void*
char *VoidPropPalPal(void *pp);

// Retorna a palavra armazenada emtPropriedadePal
char *PropPalPal(tPropriedadePal_pt);

// Retorna a frequência aramazenada
int PropPalFreq(tPropriedadePal_pt);

// Compara a palavra contida em tProrpriedadePal utilizando strcmp
int CompPal(const void *i1, const void *i2);

// Libera da memória um tPropriedadePal
void LiberaPropPal(void *);

#endif