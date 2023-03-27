#ifndef _TPROG2_H_
#define _TPROG2_H_
#include "tLista.h"
#include "utils.h"

// Identifica a "moda" entre os k primeiros
char *ModaDeClasse(tLista_pt l, tLista_pt docs, int k);

// Intermedia e exbibe resultados de uma busca
void ExibirBusca(char *busca, tListaHash_pt lh, tLista_pt docs);

// Realiza a busca de um ou mais termos e retorna uma lista com os
// tPropriedadeDocs dos documentos mais similares a busca em ordem de relevância
tLista_pt Buscar(char *busca, tListaHash_pt lh, tLista_pt docs);

// Utiliza o algoritimo k nearest neighbor para predizer a classe de um dado
// texto
char *KNN(char *busca, tListaHash_pt lh, tLista_pt docs, int k);

// Função de comparação entre 2 documentos para ser utilizada pela função KNN
double comparar(tDocumento_pt doc1, tDocumento_pt doc2, tListaHash_pt lh,
                int n_docs);

// Gera uma lista com o número de aparições de uma palavra por documento e
// retorna uma lista, imprime na tela e retorna essa lista
tLista_pt AparicoesDePalavraEmDocumento(tLista_pt docs, tPalavra_pt p);

// Imprime na tela o número de aparições de uma palavra por classe de documento
// a partir da lista de aparições em documentos
void AparicoesDePalavraPorClasse(tLista_pt ClasseEFreqNoDoc);

// Gera um relatório de uma palavra dada e exibe no terminal
void RelatorioDePalavras(char *palavra, tListaHash_pt lh, tLista_pt docs);

// Gera um relatório de todos os documentos e imprime no terminal
void RelatorioDeDocumentos(tLista_pt docs);

// Carregar dados processados de uma sequencia de documentos
tLista_pt AbrirListaDocumento(const char *filename);

// Carregar uma lista hash a partir de um arquivo
tListaHash_pt AbrirListaHash(const char *filename);

#endif