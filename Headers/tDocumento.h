#ifndef _TDOCUMENTO_H_
#define _TDOCUMENTO_H_
#include "tLista.h"
#include "tListaHash.h"
#include "tPalavra.h"
#include "tPropriedadePal.h"
#include <stdlib.h>
#include <string.h>

// Ponteiro para o tipo
typedef struct tDocumento_st *tDocumento_pt;

// Calcula (se necessário) e retorna o número de palavras em um documento
int DocNPals(tDocumento_pt doc);

// Carrega uma lista de tDocumentos com documentos em path. pode continuar a
// preecher uma lista ou começar uma nova com null
tLista_pt CarregarDocumentos(const char *path, tLista_pt ListaDocumentos);

// Carreta um novo tDocumento e retorna o ponteiro dele
tDocumento_pt CarregaUMDocumento(char *path);

// Realiza a contagem de palavras de todos os documentos
void ContagemDePalavras(tListaHash_pt lh, tLista_pt ListaDocumentos);

// Retorna o tamanho de um arquivo de documento
int ObterTAM_Arquivo(FILE *arquivo);

// Retorna um novo struct de documento recebendo os itens ou NULL para itens
// vazios
tDocumento_pt InicializaNovoDocumento(int idx, char *conteudo, int size,
                                      char *tipo, char *caminho);

// Retorna a tLista de frequência das palavras
tLista_pt DocPalsFreq(tDocumento_pt doc);

// Retorna o tipo do documento em tDocumento
char *DocTipo(tDocumento_pt doc);

// Retorna o tamanho de um documento
int DocSize(tDocumento_pt doc);

// Retorna o index original na lista de documentos de um documento
int DocIdx(tDocumento_pt doc);

// Retorna o conetúdo de um documento
char *DocConteudo(tDocumento_pt doc);

// Retorna o diretório onde se encontra o documento
char *DocCaminho(tDocumento_pt doc);

// Contabiliza as palavras em um documento para o indice de documentos e retorna
// uma lista de palavras para o índice de palavras
tLista_pt IndiceDeDocumentos(tDocumento_pt documento);

// Adiciona ao índice de palavras a lista de palavras de um documento
void IndiceDePalavras(tListaHash_pt lh, tLista_pt Palavras, int idx);

// Valor da frequência de uma determinada palavra em um determinado documento
double TF(tDocumento_pt d, char *pal);

// Comprara dois tamanhos de documentos
int CompDocTamDec(const void *i1, const void *i2);

// Comprara dois tamanhos de documentos de forma invertida
int CompDocTamCres(const void *i1, const void *i2);

// Imprime informações sobre um documento
void Imprime(tDocumento_pt doc);

// Libera um documento da memória
void LiberaDocumento(void *);

#endif