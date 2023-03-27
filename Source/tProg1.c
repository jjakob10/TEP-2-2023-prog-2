#include "../Headers/tProg1.h"
#include "../Headers/tLista.h"
#include "../Headers/tListaHash.h"
#include <stdio.h>
#include <stdlib.h>

void SalvarListaHash(tListaHash_pt data, const char *filename) {

  FILE *arq = fopen(filename, "wb");
  int i, J, K, QTD_Props, QTD_IT_Lista;
  int TamLH = ObterTamanhoListaHash(data);
  int QTD_Hash = qtdHash(data);
  char esc = '\0';
  if (arq == NULL) {
    printf("SALVAR L-HASH | Nao foi possivel gerar o arquivo\n");
    exit(EXIT_FAILURE);
  }

  tLista_pt ListaAtual, ListaPropPal;
  tPalavra_pt PalAtual;

  tPropriedadeDoc_pt PropAtual;
  int index, freq;
  float TF_IDF;

  fwrite(&TamLH, sizeof(int), 1, arq);
  fwrite(&QTD_Hash, sizeof(int), 1, arq);

  for (i = 0; i < qtdHash(data); i++) {

    ListaAtual = AcessaIdx(data, i);

    QTD_IT_Lista = qtd(ListaAtual);
    fwrite(&QTD_IT_Lista, sizeof(int), 1, arq);
    for (J = 0; J < qtd(ListaAtual); J++) {

      PalAtual = Acessa(ListaAtual, J);

      int size = strlen(PalavraPal(PalAtual));

      fwrite(&size, sizeof(int), 1, arq);
      fwrite(PalavraPal(PalAtual), sizeof(char), size, arq);
      fwrite(&esc, sizeof(char), 1, arq);

      size = 0;

      ListaPropPal = PalProps(PalAtual);
      QTD_Props = qtd(ListaPropPal);

      fwrite(&QTD_Props, sizeof(int), 1, arq);
      for (K = 0; K < qtd(ListaPropPal); K++) {

        PropAtual = Acessa(ListaPropPal, K);
        index = PropDocIdx(PropAtual);
        freq = PropDocFreq(PropAtual);
        TF_IDF = PropDocTFIDF(PropAtual);

        fwrite(&index, sizeof(int), 1, arq);
        fwrite(&freq, sizeof(int), 1, arq);
        fwrite(&TF_IDF, sizeof(float), 1, arq);
      }
    }
  }
  fclose(arq);
}

void SalvarListaDocumento(tLista_pt data, const char *filename) {
  FILE *arq = fopen(filename, "wb+");
  int i, J, TamLista = qtd(data), QTD_Props = 0, freq, TamTipo, TamConteudo,
            TamPPalConteudo, TamCaminho;
  char esc = '\0', *Conteudo, *Tipo, *PropPal, *caminho;

  tLista_pt Propriedades;
  tDocumento_pt DocumentoAtual;
  tPropriedadePal_pt PropAtual;

  fwrite(&TamLista, sizeof(int), 1, arq);

  for (i = 0; i < TamLista; i++) {
    DocumentoAtual = (tDocumento_pt)Acessa(data, i);
    TamConteudo = DocSize(DocumentoAtual);
    Tipo = DocTipo(DocumentoAtual);
    caminho = DocCaminho(DocumentoAtual);
    TamCaminho = strlen(caminho);
   
    fwrite(Tipo, sizeof(char), TYPE_SIZE, arq);
    fwrite(&TamConteudo, sizeof(int), 1, arq);
    
    fwrite(&TamCaminho, sizeof(int), 1, arq);
    fwrite(caminho, sizeof(char), TamCaminho, arq);

    Propriedades = DocPalsFreq(DocumentoAtual);
    QTD_Props = qtd(Propriedades);

    fwrite(&QTD_Props, sizeof(int), 1, arq);

    for (J = 0; J < QTD_Props; J++) {
      PropAtual = Acessa(Propriedades, J);
      PropPal = PropPalPal(PropAtual);
      freq = PropPalFreq(PropAtual);
      TamPPalConteudo = strlen(PropPal);
      fwrite(&TamPPalConteudo, sizeof(int), 1, arq);
      fwrite(PropPal, sizeof(char), TamPPalConteudo, arq);
      fwrite(&freq, sizeof(int), 1, arq);
    }
  }
  fclose(arq);
}
