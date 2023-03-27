// Ponteiro de Lista hash
typedef struct tListaHash_st *tListaHash_pt;

// Define e trata das funcionalidades do TAD tListaHash
#ifndef _TLISTAHASH_H_
#define _TLISTAHASH_H_

// constante para a função hash (N° primo de Mersenne comumente usado para tal)
#define G 31

#include "tLista.h"
#include "tPalavra.h"
#include "utils.h"
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Faz a alocacao inical da lista
tListaHash_pt InicializaListaHash(int tam);

// Adiciona um novo elemento na lista
void addHash(tListaHash_pt lh, void *item);

// Retorna a quantidade de listas já registradas na hash table
int qtdHash(tListaHash_pt lh);

// Acessa um item da lista hash pelo item
tLista_pt AcessaHash(tListaHash_pt lh, char *item);

// Realiza acesso automático à lista hash e retorna struct da palavra
// selecionada ou NULL caso ela não exita
tPalavra_pt ObtemPalavraDeListaHash(tListaHash_pt lh, char *pal);

// Acessa um item da lista hash pelo index de registro
tLista_pt AcessaIdx(tListaHash_pt lh, int idx);

// Retorna o tamanho total alocado para a lista hash
int ObterTamanhoListaHash(tListaHash_pt lh);

// Libera uma lista independente do seu tipo
void LiberaListaHash(tListaHash_pt lh);


#endif