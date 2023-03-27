#include "../Headers/tTipo.h"

typedef struct tTipo_st {
  char *classe;
  int freq;
} tTipo;

void *NovoVoidTipo(char *classe, int freq) { return NovoTipo(classe, freq); }

tTipo_pt NovoTipo(char *classe, int freq) {
  tTipo_pt t = malloc(sizeof(tTipo));
  t->classe = classe;
  t->freq = freq;
  return t;
}

char *VoidTipoClasse(void *t) { return ((tTipo_pt)t)->classe; }

int VoidTipoFreq(void *t) { return ((tTipo_pt)t)->freq; }

char *TipoClasse(tTipo_pt t) { return t->classe; }

int TipoFreq(tTipo_pt t) { return t->freq; }

void SetFreq(tTipo_pt t, int freq) { t->freq = freq; }

int CompTipoRev(const void *i1, const void *i2) { return CompTipo(i2, i1); }

int CompTipo(const void *i1, const void *i2) {
  tTipo_pt *t1 = (tTipo_pt *)i1;
  tTipo_pt *t2 = (tTipo_pt *)i2;
  return strcmp((*t1)->classe, (*t2)->classe);
}
int CompFreqTipo(const void *i1, const void *i2) {
  tTipo_pt *t1 = (tTipo_pt *)i1;
  tTipo_pt *t2 = (tTipo_pt *)i2;
  return (*t2)->freq - (*t1)->freq;
}

void LiberaTipo(void *t) { free(t); }