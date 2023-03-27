#define DEBUG 0
#include "Headers/tProg2.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {

  char *dir, *dirDocs, *dirPals, *classe, texto[USERINPUT];
  int k, funcao;

  tLista_pt ListaDoc;
  tListaHash_pt lh;

  if (argc != 3 && !DEBUG) {
    printf("Argumentos esperados:");
    printf("(indices.bin) (int k)\n");
    exit(EXIT_FAILURE);
  }
  if (!DEBUG) {
    dir = RemoveExtention(argv[1]);
    sscanf(argv[2], "%d", &k);
  } else {
    dir = "saida";
    k = 3;
  }

  dirDocs = Concatenar("", dir, "Docs.bin");
  dirPals = Concatenar("", dir, "Pals.bin");
  if (!DEBUG)
    free(dir);

  lh = AbrirListaHash(dirPals);
  ListaDoc = AbrirListaDocumento(dirDocs);

  do {
    printf("Escolha uma opção:\n");
    printf("(1) Realizar busca no banco de documentos\n");
    printf("(2) Realizar predição de classe de texto\n");
    printf("(3) Gerar relatório de uma palavra\n");
    printf("(4) Gerar relatório dos documentos\n");
    printf("(5) Sair\n");
    scanf("%d", &funcao);
    if (funcao > 5 && funcao < 1)
      continue;

    switch (funcao) {
    case 1:
      scanf("%*[^\n]");
      scanf("%*c");
      printf("Digite os termos de busca: ");
      scanf("%[^\n]", texto);
      ExibirBusca(texto, lh, ListaDoc);
      break;
    case 2:
      scanf("%*[^\n]");
      scanf("%*c");
      printf("Digite os termos para a predição: ");
      scanf("%[^\n]", texto);
      classe = KNN(texto, lh, ListaDoc, k);
      printf("\n\tclasse predita: %s\n\n", classe);
      free(classe);
      break;
    case 3:
      printf("Digite uma palavra: ");
      scanf("%s", texto);
      RelatorioDePalavras(texto, lh, ListaDoc);
      break;
    case 4:
      RelatorioDeDocumentos(ListaDoc);
      break;
    }

  } while (funcao != 5);

  free(dirDocs);
  free(dirPals);
  LiberaListaHash(lh);
  LiberaLista(ListaDoc);

  return 0;
}