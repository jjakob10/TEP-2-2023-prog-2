#define DEBUG 0
#include "Headers/tProg1.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  int n_palavras;
  char *dir, *dirDocs, *dirPals;
  char *saida;
  if (argc != 3 && !DEBUG) {
    printf("Argumentos esperados:");
    printf("(dir/train.txt) (saida.bin)\n");
    exit(EXIT_FAILURE);
  }
  if (!DEBUG) {
    dir = argv[1];
    saida = RemoveExtention(argv[2]);
  } else {
    dir = "tiny/train.txt";
    saida = "saida";
  }
  dirDocs = Concatenar("", saida, "Docs.bin");
  dirPals = Concatenar("", saida, "Pals.bin");
  if (!DEBUG)
    free(saida);

  printf("Carregando documentos\n");
  tLista_pt ListaDoc = CarregarDocumentos(dir, NULL);
  tListaHash_pt lh = InicializaListaHash(TAMHASHTABLE);

  printf("Montando indice de documentos e palavras\n");
  ContagemDePalavras(lh, ListaDoc);
  printf("Calculando TFIDF\n");
  n_palavras = PreencheTFIDF(lh, ListaDoc);

  printf("Salvando indice de palavras\n");
  SalvarListaHash(lh, dirPals);
  printf("Salvando índice de documentos\n\n");
  SalvarListaDocumento(ListaDoc, dirDocs);

  printf("%d palavras diferentes salvas\n", n_palavras);
  printf("%d documentos não nulos salvos\n\n", qtd(ListaDoc));

  printf("Limpando memoria\n");
  LiberaLista(ListaDoc);
  LiberaListaHash(lh);
  free(dirDocs);
  free(dirPals);
  printf("Operação bem sucedida\n");
  return 0;
}
