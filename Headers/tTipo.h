// Definição do Ponteiro para o tipo tTipo
typedef struct tTipo_st *tTipo_pt;

#ifndef _TTIPO_H_
#define _TTIPO_H_
#include "tLista.h"
#include "tPalavra.h"
#include "utils.h"

// Aloca em memória um tTipo, mas retorna como void*
void *NovoVoidTipo(char *classe, int freq);

// Aloca em memória um tTipo
tTipo_pt NovoTipo(char *classe, int freq);

// Retorna a classe armazenada em um tTipo, mas recebendo esse como void*
char *VoidTipoClasse(void *t);

// Retorna a frequência armazenada em um tTipo, mas recebendo esse como void*
int VoidTipoFreq(void *t);

// Retorna a classe armazenada em um tTipo
char *TipoClasse(tTipo_pt t);

// Retorna a frequência armazenada em um tTipo
int TipoFreq(tTipo_pt t);

// Atualiza o valor de frequência armazenado em um tTipo
void SetFreq(tTipo_pt t, int freq);

// Função CompTipo invertida
int CompTipoRev(const void *i1, const void *i2);

// Compara dois tTipos pelo tipo (classe)
int CompTipo(const void *i1, const void *i2);

// Compara dois tTipos pela frequência da classe
int CompFreqTipo(const void *i1, const void *i2);

// Libera da memória um tTipo
void LiberaTipo(void *t);

#endif
