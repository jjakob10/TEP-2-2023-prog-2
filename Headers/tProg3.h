#ifndef _TPROG3_H_
#define _TPROG3_H_
#include "tLista.h"
#include "tPredicao.h"
#include "tProg2.h"
#include "utils.h"

// Faz a predição da classe de uma lista de documentos dada e retorna uma lista
// com os resultados preditos e esperados
tLista_pt CalculaPredicoes(tLista_pt listaTestDocs, tListaHash_pt lh,
                           tLista_pt docs, int k);

// A partir da lista de predições, gera e salva uma matriz confusão
void GeraMatrizConfusao(tLista_pt predits, char *path);

// A partir da lista de predições, calcula e salva a acurácia
void GeraESalvaAcuracia(tLista_pt predits, char *path);

// Imprime cabeçalho de um arquivo de matriz confusão contendo a lista de
// classes
void ImprimeCabecalho(FILE *arq, tLista_pt classes);

// Imprime uma linha da matriz confusão com a frequência de predição para uma
// dada classe esperada
void ImprimeContagemEmArquivo(FILE *arq, tLista_pt classes, tLista_pt contagem);
#endif
