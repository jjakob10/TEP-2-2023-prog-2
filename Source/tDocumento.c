#include "../Headers/tDocumento.h"
#include "../Headers/tLista.h"
#include "../Headers/utils.h"

typedef struct tDocumento_st {
  int idx;
  char *caminho;
  char *conteudo;
  int size;
  char tipo[TYPE_SIZE];
  tLista_pt freq_palavras;
  int qtd_pals;
} tDocumento;

int DocNPals(tDocumento_pt doc) {
  if (doc->qtd_pals)
    return doc->qtd_pals;
  int i, sum = 0;
  tPropriedadePal_pt propPal;
  for (i = 0; i < qtd(doc->freq_palavras); i++) {
    propPal = Acessa(doc->freq_palavras, i);
    sum += PropPalFreq(propPal);
  }
  doc->qtd_pals = sum;
  return doc->qtd_pals;
}

tLista_pt CarregarDocumentos(const char *path, tLista_pt ListaDocumentos) {

  char *save = NULL, *token = NULL, *fname, *pathcpy;
  tDocumento_pt documento;
  char linha[LINESIZE];
  FILE *arq_base;
  if (!ListaDocumentos)
    ListaDocumentos = InicializaLista(TAMLISTA, DOCUMENTO);

  arq_base = fopen(path, "r");
  if (!arq_base) {
    printf("Não foi possivel abrir o arquivo base %s\n", path);
    exit(EXIT_FAILURE);
  }

  pathcpy = str_trim_malloc_cpy((char *)path);

  fname = strrchr(path, '/');
  if (fname == NULL)
    fname = strrchr(path, '\\');

  pathcpy[strlen(pathcpy) - strlen(fname)] = '\0';

  while (fgets(linha, LINESIZE, arq_base) != NULL) {
    if (isspace(linha[0]))
      continue;
    token = strtok_r(linha, " ", &save);
    fname = Concatenar(pathcpy, "/", token);
    documento = CarregaUMDocumento(fname);
    documento->idx = qtd(ListaDocumentos);
    token = strtok_r(NULL, " ", &save);
    strncpy(documento->tipo, token, 3);
    documento->tipo[3] = '\0';
    if (documento->size <= 1)
      LiberaDocumento(documento);
    else
      ListaDocumentos = add(ListaDocumentos, documento);
  }
  free(pathcpy);
  fclose(arq_base);
  return ListaDocumentos;
}

tDocumento_pt CarregaUMDocumento(char *path) {

  FILE *Arquivo = fopen(path, "r");
  if (Arquivo == NULL) {
    printf("Não foi possivel abrir o arquivo %s\n", path);
    exit(EXIT_FAILURE);
  }
  int TAM_Arquivo = ObterTAM_Arquivo(Arquivo);
  tDocumento_pt NovoDocumento =
      InicializaNovoDocumento(-1, NULL, TAM_Arquivo, NULL, path);

  NovoDocumento->conteudo = (char *)malloc(sizeof(char) * TAM_Arquivo + 2);
  fgets(NovoDocumento->conteudo, TAM_Arquivo + 1, Arquivo);

  fclose(Arquivo);
  return NovoDocumento;
}

int ObterTAM_Arquivo(FILE *arquivo) {
  int tamanho;
  fseek(arquivo, 0, SEEK_END);
  tamanho = ftell(arquivo);
  rewind(arquivo);
  return tamanho;
}

tDocumento_pt InicializaNovoDocumento(int idx, char *conteudo, int size,
                                      char *tipo, char *caminho) {
  tDocumento_pt NovoDocumento = (tDocumento *)malloc(sizeof(tDocumento));
  if (idx > -1)
    NovoDocumento->idx = idx;
  else
    NovoDocumento->idx = -1;
  if (conteudo)
    NovoDocumento->conteudo = str_trim_malloc_cpy(conteudo);
  else
    NovoDocumento->conteudo = NULL;
  if (size)
    NovoDocumento->size = size;
  else
    NovoDocumento->size = 0;
  if (tipo)
    strcpy(NovoDocumento->tipo, tipo);
  else
    strcpy(NovoDocumento->tipo, "   ");

  NovoDocumento->caminho = caminho;
  NovoDocumento->qtd_pals = 0;
  NovoDocumento->freq_palavras = InicializaLista(TAMLISTA, PROPRIEDADEPAL);
  return NovoDocumento;
}

tLista_pt DocPalsFreq(tDocumento_pt doc) { return doc->freq_palavras; }

char *DocTipo(tDocumento_pt doc) { return doc->tipo; }

int DocSize(tDocumento_pt doc) { return doc->size; }

int DocIdx(tDocumento_pt doc) { return doc->idx; }

char *DocConteudo(tDocumento_pt doc) { return doc->conteudo; }

char *DocCaminho(tDocumento_pt doc) { return doc->caminho; }

void ContagemDePalavras(tListaHash_pt lh, tLista_pt ListaDocumentos) {
  int i;
  tDocumento_pt documento;
  tLista_pt Palavras;
  for (i = 0; i < qtd(ListaDocumentos); i++) {
    documento = Acessa(ListaDocumentos, i);
    Palavras = IndiceDeDocumentos(documento);
    IndiceDePalavras(lh, Palavras, i);
  }
}

void IndiceDePalavras(tListaHash_pt lh, tLista_pt Palavras, int idx) {
  int i;
  tPropriedadePal_pt p;
  for (i = 0; i < qtd(Palavras); i++) {
    p = Acessa(Palavras, i);
    addFreq(lh, PropPalPal(p), idx);
  }
  LiberaLista(Palavras);
}

tLista_pt IndiceDeDocumentos(tDocumento_pt documento) {
  tLista_pt Palavras;

  Palavras = StrToPropPalList(documento->conteudo);

  OrdenaLista(Palavras, CompPal);

  ContagemEmLista(documento->freq_palavras, Palavras, CompPal, NovaVoidPropPal,
                  ReturnOne, VoidPropPalPal);
  return Palavras;
}

double TF(tDocumento_pt d, char *pal) {
  tPropriedadePal_pt busca = NovaPropPal(pal, 0);
  tPropriedadePal_pt *pp = ListaBsearch(d->freq_palavras, busca, CompPal);
  LiberaPropPal(busca);
  if (pp == NULL)
    return 0.0;
  return PropPalFreq(*pp);
}

int CompDocTamDec(const void *i1, const void *i2) {
  tDocumento_pt *d1 = (tDocumento_pt *)i1;
  tDocumento_pt *d2 = (tDocumento_pt *)i2;
  return DocNPals((*d1)) - DocNPals((*d2));
}

int CompDocTamCres(const void *i1, const void *i2) {
  return CompDocTamDec(i2, i1);
}

void Imprime(tDocumento_pt doc) { printf("Referência: %s\n", doc->caminho); }

void LiberaDocumento(void *item) {
  tDocumento_pt doc = (tDocumento_pt)item;
  if (doc->conteudo)
    free(doc->conteudo);
  if (doc->caminho)
    free(doc->caminho);
  LiberaLista(doc->freq_palavras);
  free(doc);
}
