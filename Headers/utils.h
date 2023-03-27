#ifndef _UTILS_H_
#define _UTILS_H_

// Definição de constantes
#define USERINPUT 1000
#define TAMLISTA 10
#define TAMLISTASMALL 3
#define TAMHASHTABLE 1000000
#define RESULTADOS_PESQUISA 10
#define PRTQTD 10
#define LINESIZE 2500
#define TYPE_SIZE 4

#include "tLista.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Remove espaços em volta de uma string, aloca uma cópia e retorna o ponteiro
char *str_trim_malloc_cpy(char *str2);

// Remove espaços em volta de uma string e copia essa para o endereço dado
void str_trim_cpy(char *str1, char *str2);

// Transforma todos os carateres de uma string em minúsculos
char *toLowerStr(char *str);

// Concatena três strings e retorna em uma só
char *Concatenar(const char *str1, const char *str2, const char *str3);

// Transforma uma string em uma lista de propriedades de palavras
tLista_pt StrToPropPalList(char *string);

// Retorna 1 para qualquer parâmetro dado (função auxiliar para o mecanismo de
// contágem)
int ReturnOne(void *i);

// Remove a extenção de um nome de arquivo
char *RemoveExtention(char *str);

#endif