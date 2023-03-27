#include "../Headers/tPropriedadeDoc.h"

typedef struct tPropriedadeDoc_st {
  int idx;
  int freq;
  float TFIDF;
} tPropriedadeDoc;

tPropriedadeDoc_pt NovaPropDoc(int idx, int freq) {
  tPropriedadeDoc_pt pd = malloc(sizeof(tPropriedadeDoc));
  pd->idx = idx;
  pd->freq = freq;
  pd->TFIDF = -1;
  return pd;
}

tPropriedadeDoc_pt CopiaPropDoc(tPropriedadeDoc_pt pd1) {
  tPropriedadeDoc_pt pd2 = malloc(sizeof(tPropriedadeDoc));
  pd2->idx = pd1->idx;
  pd2->freq = pd1->freq;
  pd2->TFIDF = pd1->TFIDF;
  return pd2;
}

void SetPropDocFreq(tPropriedadeDoc_pt pd, int freq) { pd->freq = freq; }

void SetPropDocTFIDF(tPropriedadeDoc_pt pd, float TFIDF) { pd->TFIDF = TFIDF; }

int PropDocIdx(tPropriedadeDoc_pt pd) { return pd->idx; }

int PropDocFreq(tPropriedadeDoc_pt pd) { return pd->freq; }

float PropDocTFIDF(tPropriedadeDoc_pt pd) { return pd->TFIDF; }

int CompTFIDF(const void *i1,const void *i2){
  tPropriedadeDoc_pt *pp1 = (tPropriedadeDoc_pt*)i1;
  tPropriedadeDoc_pt *pp2 =(tPropriedadeDoc_pt*)i2;
  float dif = (*pp1)->TFIDF - (*pp2)->TFIDF;
  if(dif > 0) return -1;
  if(dif< 0) return 1;
  return 0;
}

int CompFreq(const void *i1,const void *i2){
  tPropriedadeDoc_pt *pp1 = (tPropriedadeDoc_pt*)i1;
  tPropriedadeDoc_pt *pp2 =(tPropriedadeDoc_pt*)i2;
  return (*pp2)->freq - (*pp1)->freq;
}

void LiberaPropDoc(void *pd) { free(pd); }