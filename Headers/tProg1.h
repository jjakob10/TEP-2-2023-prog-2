#ifndef _TPROG1_H_
#define _TPROG1_H_
#include "../Headers/tLista.h"
#include "tPropriedadeDoc.h"

// Salva a lista hash em um arquivo "filename".bin
void SalvarListaHash(tListaHash_pt data, const char *filename);

// Salva uma lista processada de documentos
void SalvarListaDocumento(tLista_pt data, const char *filename);


#endif