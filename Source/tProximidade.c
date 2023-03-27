#include "../Headers/tProximidade.h"

typedef struct tProximidade_st {
  int idx;
  double prox;
} tProximidade;

tProximidade_pt NovaProximidade(int idx, double prox) {
  tProximidade_pt px = malloc(sizeof(tProximidade));
  px->idx = idx;
  px->prox = prox;
  return px;
}
int ProxIdx(tProximidade_pt px) { return px->idx; }
double ProxProx(tProximidade_pt px) { return px->prox; }

int CompProx(const void *i1, const void *i2) {
  tProximidade_pt *px1 = (tProximidade_pt *)i1;
  tProximidade_pt *px2 = (tProximidade_pt *)i2;
  double dif = (*px2)->prox - (*px1)->prox;
  if (dif < 0)
    return -1;
  if (dif > 0)
    return 1;
  return 0;
}

void LiberaProx(void *px) { free(px); }