#include "../Headers/tPropriedadePal.h"

typedef struct tPropriedadePal_st {
  char *pal;
  int freq;
} tPropriedadePal;

void *NovaVoidPropPal(char *pal, int freq)  {
  return NovaPropPal(pal, freq);
}

tPropriedadePal_pt NovaPropPal(char *pal, int freq)  {
  tPropriedadePal_pt pp = malloc(sizeof(tPropriedadePal));
  pp->pal = str_trim_malloc_cpy(pal);
  pp->freq = freq;
  return pp; 
}

char *VoidPropPalPal(void *pp) { return ((tPropriedadePal_pt)pp)->pal; }

char *PropPalPal(tPropriedadePal_pt pp) { return pp->pal; }

int PropPalFreq(tPropriedadePal_pt pp) { return pp->freq; }

int CompPal(const void *i1,const void *i2){
  tPropriedadePal_pt *pp1 = (tPropriedadePal_pt*)i1;
  tPropriedadePal_pt *pp2 = (tPropriedadePal_pt*)i2;
  return strcmp((*pp1)->pal,(*pp2)->pal);
}

void LiberaPropPal(void *pp) {
  free(((tPropriedadePal_pt)pp)->pal);
  free(pp);
}