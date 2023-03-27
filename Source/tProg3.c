#include "../Headers/tProg3.h"

tLista_pt CalculaPredicoes(tLista_pt listaTestDocs, tListaHash_pt lh,
                           tLista_pt docs, int k) {
  int i;
  char *classe_pred;
  tDocumento_pt testDoc;
  tPredicao_pt pred;
  tLista_pt predits = InicializaLista(TAMLISTA, PREDICAO);
  for (i = 0; i < qtd(listaTestDocs); i++) {
    printf("%d de %d\n",i,qtd(listaTestDocs));
    testDoc = Acessa(listaTestDocs, i);
    classe_pred = KNN(DocConteudo(testDoc), lh, docs, k);
    pred = NovaPredicao(i, DocTipo(testDoc), classe_pred);
    predits = add(predits, pred);
    free(classe_pred);
  }
  return predits;
}

void GeraMatrizConfusao(tLista_pt predits, char *path) {
  int i, fimContagem = 0, inicioContagem = 0;

  FILE *arq;
  tTipo_pt t;
  tLista_pt classes = InicializaLista(TAMLISTA, TIPO);
  tLista_pt cont;

  arq = fopen(path, "w");

  OrdenaLista(predits, CompRealPred);
  ContagemEmLista(classes, predits, CompReal, NovoVoidTipo, ReturnOne, VoidPredReal);
  ImprimeCabecalho(arq, classes);

  for (i = 0; i < qtd(classes); i++) {
    t = Acessa(classes, i);
    cont = InicializaLista(TAMLISTA, TIPO);
    fimContagem += TipoFreq(t);
    SetDiv1(predits, inicioContagem);
    SetDiv2(predits, fimContagem);
    ContagemEmLista(cont, predits, CompPred, NovoVoidTipo, ReturnOne, VoidPredPredita);
    fprintf(arq, " %s", TipoClasse(t));
    ImprimeContagemEmArquivo(arq, classes, cont);
    LiberaLista(cont);
    inicioContagem = fimContagem;
  }
  LiberaLista(classes);
  fclose(arq);
}

void GeraESalvaAcuracia(tLista_pt predits, char *path) {
  int i, acertos = 0;
  FILE *arq = fopen(path, "a");
  tPredicao_pt p;
  for (i = 0; i < qtd(predits); i++) {
    p = Acessa(predits, i);
    acertos += PredicaoCerta(p);
  }
  fprintf(arq, "\n\nAcuracia: %lf%%",
          100.0 * ((double)acertos / (double)qtd(predits)));
  fclose(arq);
}

void ImprimeContagemEmArquivo(FILE *arq, tLista_pt classes,
                                     tLista_pt contagem) {
  int i;
  tTipo_pt t, classe;
  tTipo_pt *busca;

  for (i = 0; i < qtd(classes); i++) {
    classe = Acessa(classes, i);
    t = NovoTipo(TipoClasse(classe), 0);
    busca = ListaBsearch(contagem, t, CompTipo);

    if (busca == NULL)
      fprintf(arq, "   0 ");
    else
      fprintf(arq, " %3d ", TipoFreq(*busca));

    LiberaTipo(t);
  }
  fprintf(arq, "\n");
}

void ImprimeCabecalho(FILE *arq, tLista_pt classes) {
  int i;
  tTipo_pt t;
  fprintf(arq, "    ");
  for (i = 0; i < qtd(classes); i++) {
    t = Acessa(classes, i);
    fprintf(arq, " %s ", TipoClasse(t));
  }
  fprintf(arq, "\n");
}