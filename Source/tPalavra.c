#include "../Headers/tPalavra.h"
#include "../Headers/tLista.h"
#include "../Headers/tListaHash.h"

typedef struct tPalavra_st {
  char *pal;
  tLista_pt prop;
} tPalavra;

tPalavra_pt NovaPalavra(char *pal) {
  tPalavra_pt p = malloc(sizeof(tPalavra));
  p->pal = str_trim_malloc_cpy(pal);
  p->prop = InicializaLista(TAMLISTA, PROPRIEDADEDOC);
  return p;
}

char *PalavraPal(tPalavra_pt p) { return p->pal; }

tLista_pt PalProps(tPalavra_pt p) { return p->prop; }

void addProp(tPalavra_pt p, tPropriedadeDoc_pt i) { p->prop = add(p->prop, i); }

void addFreq(tListaHash_pt lh, char *pal, int idx) {
  int i;
  tPalavra_pt p;
  tPropriedadeDoc_pt pd;

  p = ObtemPalavraDeListaHash(lh, pal);
  if (p == NULL) {
    p = NovaPalavra(pal);
    addHash(lh, p);
  }

  if (qtd(p->prop))
    pd = Acessa(p->prop, qtd(p->prop) - 1);
  else
    pd = NULL;

  if (!pd || PropDocIdx(pd) != idx) {
    pd = NovaPropDoc(idx, 1);
    p->prop = add(p->prop, pd);
  } else {
    SetPropDocFreq(pd, PropDocFreq(pd) + 1);
  }
}

int PreencheTFIDF(tListaHash_pt lh, tLista_pt docs) {
  int i, j, k, n_palavras = 0;
  double idf, tf;
  tLista_pt lpals;
  tPalavra_pt p;
  tDocumento_pt d;
  tPropriedadeDoc_pt pd;

  for (i = 0; i < qtdHash(lh); i++) {
    lpals = AcessaIdx(lh, i);

    for (j = 0; j < qtd(lpals); j++) {
      p = Acessa(lpals, j);
      idf = IDF(qtd(p->prop), qtd(docs));
      n_palavras++;
      for (k = 0; k < qtd(p->prop); k++) {
        pd = Acessa(p->prop, k);
        d = Acessa(docs, PropDocIdx(pd));
        tf = TF(d, PalavraPal(p));

        SetPropDocTFIDF(pd, tf * idf);
      }
    }
  }
  return n_palavras;
}

double IDF(int df, int n_docs) { return 1 + log((1.0 + n_docs) / (1.0 + df)); }

void LiberaPalavra(void *p) {
  free(((tPalavra_pt)p)->pal);
  LiberaLista(((tPalavra_pt)p)->prop);
  free(p);
}
