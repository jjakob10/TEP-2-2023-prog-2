#define DEBUG 0
#include "Headers/tProg3.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  tLista_pt ListaDoc, TestDocs, predits;
  tListaHash_pt lh;
  char *dir, *dirDocs, *dirPals, *dirTest, *saida;
  ;
  int k;
  if (argc != 5 && !DEBUG) {
    printf("Argumentos esperados:");
    printf("(indices.bin) (dir/test.txt) (int k) (saida.txt)\n");
    exit(EXIT_FAILURE);
  }
  if (!DEBUG) {
    dir = RemoveExtention(argv[1]);
    dirTest = argv[2];
    sscanf(argv[3], "%d", &k);
    saida = argv[4];
  } else {
    dir = "saida";
    dirTest = "medium-small/test.txt";
    k = 3;
    saida = "matriz.txt";
  }

  dirDocs = Concatenar("", dir, "Docs.bin");
  dirPals = Concatenar("", dir, "Pals.bin");
  if(!DEBUG)free(dir);

  printf("Carregando documentos em memória\n");
  lh = AbrirListaHash(dirPals);
  ListaDoc = AbrirListaDocumento(dirDocs);
  TestDocs = CarregarDocumentos(dirTest, NULL);

  printf("Realizando predições\n");
  predits = CalculaPredicoes(TestDocs, lh, ListaDoc, k);
  printf("Gerando matriz confusão e calculando acuracia\n");
  GeraMatrizConfusao(predits, saida);
  GeraESalvaAcuracia(predits, saida);
 
  printf("Limpando memoria\n");
  free(dirDocs);
  free(dirPals);
  LiberaListaHash(lh);
  LiberaLista(predits);
  LiberaLista(TestDocs);
  LiberaLista(ListaDoc);
  printf("Operação bem sucedida\n");

  return 0;
}