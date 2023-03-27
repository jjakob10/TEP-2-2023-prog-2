#include "../Headers/tLista.h"

typedef void (*fptr)(void *);

typedef struct tLista_st {
  void **array;
  enum TIPO tipo;
  int divisao1;
  int divisao2;
  int qtd;
  int tam;
} tLista;

static int tamanhoDoTipo(enum TIPO tipo);
static fptr selecionaLibera(enum TIPO tipo);

tLista_pt InicializaLista(int tam, enum TIPO tipo) {
  tLista_pt l = malloc(sizeof(tLista));
  l->array = malloc(tam * tamanhoDoTipo(tipo));
  l->tipo = tipo;
  l->qtd = 0;
  l->tam = tam;
  l->divisao1 = -1;
  l->divisao2 = -1;
  return l;
}

void SetDiv1(tLista_pt l, int idx) { l->divisao1 = idx; }

void SetDiv2(tLista_pt l, int idx) { l->divisao2 = idx; }

int qtdDiv1(tLista_pt l) { return l->divisao1 >= 0 ? l->divisao1 : 0; }

int qtdDiv2(tLista_pt l) { return l->divisao2 >= 0 ? l->divisao2 : l->qtd; }

tLista_pt add(tLista_pt l, void *item) {

  if (l->qtd >= l->tam) {
    l->tam *= 2;
    l->array = realloc(l->array, l->tam * tamanhoDoTipo(l->tipo));
    if (l == NULL) {
      printf("Não foi possível realocar uma lista");
      exit(11);
    }
  }

  l->array[l->qtd] = item;
  l->qtd += 1;
  return l;
}

tLista_pt CriaCopiaDeLista(tLista_pt l) {
  int i;
  tLista_pt lcpy = InicializaLista(qtd(l), l->tipo);
  for (i = 0; i < qtd(l); i++)
    lcpy = add(lcpy, Acessa(l, i));
  return lcpy;
}

void *Acessa(tLista_pt l, int index) { return l->array[index]; }

int qtd(tLista_pt l) { return l->qtd; }

void Set(tLista_pt l, int index, void *item) { l->array[index] = item; }

void OrdenaLista(tLista_pt l, fcomp_pt compara) {
  qsort(l->array, qtd(l), sizeof(void *), compara);
}

void *ListaBsearch(tLista_pt l, void *item, fcomp_pt compara) {
  return bsearch(&item, l->array, qtd(l), sizeof(void *), compara);
}

void LiberaLista(tLista_pt l) {
  int i;
  fptr Libera = selecionaLibera(l->tipo);
  for (i = 0; i < l->qtd; i++) {
    Libera(l->array[i]);
  }
  free(l->array);
  free(l);
}

void LiberaCopiaDeLista(tLista_pt l) {
  int i;
  free(l->array);
  free(l);
}

static int tamanhoDoTipo(enum TIPO tipo) { return sizeof(void *); }

static fptr selecionaLibera(enum TIPO tipo) {
  switch (tipo) {
  case PALAVRA:
    return LiberaPalavra;
  case DOCUMENTO:
    return LiberaDocumento;
  case PROPRIEDADEPAL:
    return LiberaPropPal;
  case PROPRIEDADEDOC:
    return LiberaPropDoc;
  case INT:
    return free;
  case PROXIMIDADE:
    return LiberaProx;
  case TIPO:
    return LiberaTipo;
  case PREDICAO:
    return LiberaPredicao;
  }
  return NULL;
}

void ContagemEmLista(tLista_pt destino, tLista_pt origem, fcomp_pt compara,
                     fnovo_pt NovoItem, fadd_pt soma_freq, fpal_pt ObtemPal) {

  int i, cont = 0;
  void *anterior, *atual, *item;
  anterior = Acessa(origem, qtdDiv1(origem));
  cont = soma_freq(anterior);
  for (i = qtdDiv1(origem) + 1; i < qtdDiv2(origem); i++) {
    atual = Acessa(origem, i);
    if (compara(&anterior, &atual) == 0) {
      cont += soma_freq(atual);
    } else {
      item = NovoItem(ObtemPal(anterior), cont);
      destino = add(destino, item);
      cont = soma_freq(atual);
    }

    anterior = atual;
  }
  item = NovoItem(ObtemPal(anterior), cont);
  destino = add(destino, item);
}