/// Ponteiro de Lista
typedef struct tLista_st *tLista_pt;

// Ponteiro para funções de comparação
typedef int (*fcomp_pt)(const void *, const void *);

// Ponteiro para função de criar novo item (char*, int)
typedef void *(*fnovo_pt)(char *, int);

// Ponteiro para função de adição de frequência
typedef int (*fadd_pt)(void *);

// Ponteiro para função de obter palavra de um tipo
typedef char* (*fpal_pt)(void *);



// Define e trata das funcionalidades do TAD tLista
#ifndef _TLISTA_H_
#define _TLISTA_H_
#include "tDocumento.h"
#include "tPalavra.h"
#include "tPredicao.h"
#include "tPropriedadeDoc.h"
#include "tPropriedadePal.h"
#include "tProximidade.h"
#include "tTipo.h"
#include "utils.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// tipos possiveis de lista
enum TIPO {
  PALAVRA = 0,
  DOCUMENTO = 1,
  PROPRIEDADEPAL = 2,
  PROPRIEDADEDOC = 3,
  INT = 4,
  PROXIMIDADE = 5,
  TIPO = 6,
  PREDICAO = 7
};

// Faz a alocacao inical da lista e salva o seu tipo
tLista_pt InicializaLista(int tam, enum TIPO tipo);

// Adiciona um novo elemento na lista (note que o elemento tem que ser do mesmo
// tipo que o definido na inicializacao)
tLista_pt add(tLista_pt l, void *item);

//Cria um marcador1 de divisão da lista
void SetDiv1(tLista_pt l,int idx);

//Cria um marcador2 de divisão da lista
void SetDiv2(tLista_pt l,int idx);

//Retorna um marcador 1 ou o valor 0 como indice se não existir marcador
int qtdDiv1(tLista_pt l);

//Retorna um marcador 2 ou a posição do ultimo item se não existir marcador
int qtdDiv2(tLista_pt l);

// Aloca e copia itens em uma nova lista retornada
tLista_pt CriaCopiaDeLista(tLista_pt l);

// Acessa um item da lista pelo index
void *Acessa(tLista_pt l, int index);

// Retorna a quantidade de itens em uma lista
int qtd(tLista_pt l);

// Sobrescreve uma posição da lista
void Set(tLista_pt l, int index, void *item);

// Ordena uma lista de forma decrescente
void OrdenaLista(tLista_pt l, fcomp_pt compara);

// Realiza a busca binária na lista
void *ListaBsearch(tLista_pt l, void *item, fcomp_pt compara);

// Libera uma lista independente do seu tipo
void LiberaLista(tLista_pt l);

// Libera uma copia de lista ignorando os elementos internos
void LiberaCopiaDeLista(tLista_pt l);


// Preenche uma lista recebida por referência com uma estrutura contendo nome do item e frequência que aparece na origem
void ContagemEmLista(tLista_pt destino, tLista_pt origem, fcomp_pt compara,
                          fnovo_pt NovoItem,fadd_pt soma_freq, fpal_pt ObtemPal);

#endif