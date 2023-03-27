//Ponteiro para o tipo tPropriedadeDoc
typedef struct tPropriedadeDoc_st *tPropriedadeDoc_pt;

#ifndef _TPROPRIEDADEDOC_H_
#define _TPROPRIEDADEDOC_H_
#include "tLista.h"
#include "utils.h"

//Inicializa uma nova estrutura de propriedade de palavra em um documento
tPropriedadeDoc_pt NovaPropDoc(int idx, int freq);

//Inicializa uma nova estrutura de propriedade de palavra em um documento a partir de uma já existente
tPropriedadeDoc_pt CopiaPropDoc(tPropriedadeDoc_pt pd1);

//Define o valor para a frequência de uma palavra de um documento
void SetPropDocFreq(tPropriedadeDoc_pt pd, int freq);

//Define o valor para o TFIDF de uma palavra de um documento
void SetPropDocTFIDF(tPropriedadeDoc_pt pd, float TFIDF);

//Retorna o index do documento de uma dada estrutura de propriedade
int PropDocIdx(tPropriedadeDoc_pt);

//Retorna a frequência de uma palavra de um documento
int PropDocFreq(tPropriedadeDoc_pt pd);

//Retorna o TFIDF de uma palavra de um documento
float PropDocTFIDF(tPropriedadeDoc_pt pd);

//Compara o TFIDF de duas propriedades de documento
int CompTFIDF(const void *i1,const void *i2);

//Compara a frequência no documento de duas propriedades de documento
int CompFreq(const void *i1,const void *i2);

//Libera uma estrutura de propiedade de uma palavra em um documento documentos
void LiberaPropDoc(void *);

#endif



