#include "../Headers/tPredicao.h"

typedef struct tPredicao_st {
  int idx;
  char real[TYPE_SIZE];
  char predita[TYPE_SIZE];
} tPredicao;

tPredicao_pt NovaPredicao(int idx, char *real, char *predita) {
  tPredicao_pt prd = malloc(sizeof(tPredicao));
  prd->idx = idx;
  strcpy(prd->real, real);
  strcpy(prd->predita, predita);
  return prd;
}

int PredicaoCerta(tPredicao_pt pred){
  return strcmp(pred->predita,pred->real)==0;
}

char *VoidPredReal(void* pred) { return ((tPredicao_pt)pred)->real; }

char *VoidPredPredita(void *pred) { return ((tPredicao_pt)pred)->predita; }

char *PredReal(tPredicao_pt pred) { return pred->real; }

char *PredPredita(tPredicao_pt pred) { return pred->predita; }

int CompRealPred(const void *i1, const void *i2) {
  tPredicao_pt *prd1 = (tPredicao_pt *)i1;
  tPredicao_pt *prd2 = (tPredicao_pt *)i2;
  int ret;
  ret = strcmp((*prd1)->real, (*prd2)->real);
  if (ret == 0)
    ret = strcmp((*prd1)->predita, (*prd2)->predita);
  return ret;
}

int CompPred(const void *i1, const void *i2) {
  tPredicao_pt *prd1 = (tPredicao_pt *)i1;
  tPredicao_pt *prd2 = (tPredicao_pt *)i2;
  return strcmp((*prd1)->predita, (*prd2)->predita);
}

int CompReal(const void *i1, const void *i2) {
  tPredicao_pt *prd1 = (tPredicao_pt *)i1;
  tPredicao_pt *prd2 = (tPredicao_pt *)i2;
  return strcmp((*prd1)->real, (*prd2)->real);
}
void LiberaPredicao(void *prd) { free(prd); }