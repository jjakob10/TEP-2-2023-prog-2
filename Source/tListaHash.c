#include "../Headers/tListaHash.h"
#include "../Headers/tLista.h"

typedef float (*fptr)(void *);

typedef struct tListaHash_st {
  void **array;
  int tam;
  tLista_pt registro;
} tListaHash;

static int Hash(char *item, int tam);

tListaHash_pt InicializaListaHash(int tam) {
  tListaHash_pt lh = malloc(sizeof(tListaHash));
  lh->array = calloc(tam, sizeof(tLista_pt));
  lh->tam = tam;
  lh->registro = InicializaLista(TAMLISTA, INT);
  return lh;
}

void addHash(tListaHash_pt lh, void *item) {
  int hash = Hash(PalavraPal(item), lh->tam);
  tLista_pt lista = lh->array[hash];

  if (!lista) {
    lista = InicializaLista(TAMLISTASMALL, PALAVRA);
    int *idx = malloc(sizeof(int));
    *idx = hash;
    lh->registro = add(lh->registro, idx);
  }

  lh->array[hash] = add(lista, item);
}

int qtdHash(tListaHash_pt lh) { return qtd(lh->registro); }

tLista_pt AcessaHash(tListaHash_pt lh, char *item) {
  return lh->array[Hash(item, lh->tam)];
}

tPalavra_pt ObtemPalavraDeListaHash(tListaHash_pt lh, char *pal) {
  int i;
  tPalavra_pt p;
  tLista_pt palavras = AcessaHash(lh, pal);
  if (palavras == NULL) {
    return NULL;
  }

  for (i = 0; i < qtd(palavras); i++) {
    p = Acessa(palavras, i);
    if (strcmp(pal, PalavraPal(p)) == 0)
      break;
  }
  if (i == qtd(palavras)) {
    return NULL;
  }
  return p;
}

tLista_pt AcessaIdx(tListaHash_pt lh, int idx) {
  int *idxHash = Acessa(lh->registro, idx);
  return lh->array[*idxHash];
}

int ObterTamanhoListaHash(tListaHash_pt lh) { return lh->tam; }

void LiberaListaHash(tListaHash_pt lh) {
  int i, *idx;
  for (i = 0; i < qtd(lh->registro); i++) {
    idx = Acessa(lh->registro, i);
    LiberaLista(lh->array[*idx]);
  }
  LiberaLista(lh->registro);
  free(lh->array);
  free(lh);
}

static int Hash(char *item, int tam) {
  unsigned long soma = 0;
  int i = 0;
  while (item[i]) {
    soma += soma * G + item[i];
    i++;
  }
  return soma % tam;
}