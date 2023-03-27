// Ponteiro para o tipo tPalavra
typedef struct tPalavra_st *tPalavra_pt;

#ifndef _TPALAVRA_H_
#define _TPALAVRA_H_
#include "tLista.h"
#include "tPropriedadeDoc.h"
#include "tListaHash.h"
#include "utils.h"
#include <math.h>
#include <string.h>

// Inicializa uma nova estrutura de palavra
tPalavra_pt NovaPalavra(char *pal);

// Retorna o char* da palavra registrada em uma estrutura de palavra
char *PalavraPal(tPalavra_pt p);

// Retorna a lista de propriedades da palavra em diferentes arquivos
tLista_pt PalProps(tPalavra_pt p);

// Adiciona um tPropriedadeDoc manualmente
void addProp(tPalavra_pt p, tPropriedadeDoc_pt i);

// Retorna a lista de TF-IDF da palavra em diferentes arquivos
tLista_pt TFIDF_Pal(tPalavra_pt p);

// Registra +1 na frequência de uma dada palavra em um dado arquivo de index
// "idx"
void addFreq(tListaHash_pt lh, char *pal, int idx);

// Gera e preenche todos os TD-IDF de todos os tPalavras e retona o n de palavras onde o TFIDF foi calculado
int PreencheTFIDF(tListaHash_pt lh, tLista_pt docs);

// Calcula o IDF de uma palavra
double IDF(int df, int n_docs);

// Libera uma estrutura de palavra
void LiberaPalavra(void *);

#endif