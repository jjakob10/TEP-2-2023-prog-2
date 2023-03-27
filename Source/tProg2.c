#include "../Headers/tProg2.h"

char *ModaDeClasse(tLista_pt l, tLista_pt docs, int k) {
  int i, j, n_max = -1, n;
  char *tipo1, *tipo2, *t_max;
  tProximidade_pt prox;
  tDocumento_pt doc;

  for (n = 1, i = 0; i < k; i++) {
    prox = Acessa(l, i);
    doc = Acessa(docs, ProxIdx(prox));
    tipo1 = DocTipo(doc);

    for (j = i + 1; j < k; j++) {
      prox = Acessa(l, j);
      doc = Acessa(docs, ProxIdx(prox));
      tipo2 = DocTipo(doc);

      if (strcmp(tipo1, tipo2) == 0)
        n++;
    }
    if (n_max < n) {
      n_max = n;
      t_max = tipo1;
    }
  }
  return t_max;
}

void ExibirBusca(char *busca, tListaHash_pt lh, tLista_pt docs) {
  int i, n_results;
  tLista_pt resultado;
  tPropriedadeDoc_pt propdoc;
  resultado = Buscar(busca, lh, docs);
  printf("Resultados:\n");

  if (qtd(resultado) == 0)
    printf("\tNenhum documento contendo os termos foi encontrado\n\n");

  if (RESULTADOS_PESQUISA > qtd(resultado))
    n_results = qtd(resultado);
  else
    n_results = RESULTADOS_PESQUISA;

  for (i = 0; i < n_results; i++) {
    propdoc = Acessa(resultado, i);
    // printf("%lf", PropDocTFIDF(propdoc));
    printf("\tDoc id: %d\n\t", PropDocIdx(propdoc));
    Imprime(Acessa(docs, PropDocIdx(propdoc)));
  }
  printf("\n");
  LiberaLista(resultado);
}

tLista_pt Buscar(char *busca, tListaHash_pt lh, tLista_pt docs) {
  int i, idx;
  int *idxdocs = calloc(qtd(docs), sizeof(int));
  char *save = NULL, *token = NULL, *str = NULL;

  tPropriedadeDoc_pt propdoc, propdoc_cpy;
  tPalavra_pt p;
  tLista_pt palavras, propriedade, resultados;

  resultados = InicializaLista(TAMLISTA, PROPRIEDADEDOC);

  str = str_trim_malloc_cpy(busca);
  token = strtok_r(str, " ", &save);

  // Realiza busca para cada termo de pesquisa
  while (token != NULL) {
    p = ObtemPalavraDeListaHash(lh, token);
    if (p == NULL) {
      token = strtok_r(NULL, " ", &save);
      continue;
    }
    // Para cada documento de index idx, acumula o valor de TFIDF de cada termo
    // de busca nele contido
    propriedade = PalProps(p);
    for (i = 0; i < qtd(propriedade); i++) {
      propdoc = Acessa(propriedade, i);
      idx = PropDocIdx(propdoc);
      // Primeira aparição do documento 'idx' como portador de um termo
      // de busca; Cria um novo elemento no array para acumular o TFIDF
      // e marca a posição do elemento
      if (idxdocs[idx] == 0) {
        propdoc_cpy = CopiaPropDoc(propdoc);
        resultados = add(resultados, propdoc_cpy);
        idxdocs[idx] = qtd(resultados);

        // Demais aparições do documento idx; Atualiza o valor acumulado
        // do TFIDF no documento 'idx' com o valor anterior + valor TDIFD
        // da palavra atual para o documento 'idx'
      } else {
        propdoc_cpy = Acessa(resultados, idxdocs[idx] - 1);
        SetPropDocTFIDF(propdoc_cpy,
                        PropDocTFIDF(propdoc_cpy) + PropDocTFIDF(propdoc));
      }
    }
    token = strtok_r(NULL, " ", &save);
  }

  OrdenaLista(resultados, CompTFIDF);

  free(str);
  free(idxdocs);
  return resultados;
}

char *KNN(char *busca, tListaHash_pt lh, tLista_pt docs, int k) {
  int i;
  double proximidade;
  char *t_max, *resultado;
  tDocumento_pt doc, busca_doc;
  tLista_pt l;
  tProximidade_pt prox;

  busca_doc = InicializaNovoDocumento(-1, busca, 0, NULL, NULL);
  l = IndiceDeDocumentos(busca_doc);
  LiberaLista(l);
  l = InicializaLista(qtdDiv2(docs), PROXIMIDADE);

  for (i = 0; i < qtdDiv2(docs); i++) {
    doc = Acessa(docs, i);
    proximidade = comparar(busca_doc, doc, lh, qtd(docs));
    prox = NovaProximidade(i, proximidade);
    l = add(l, prox);
  }

  OrdenaLista(l, CompProx);
  for (i = 0; i < qtd(l); i++) {
    prox = Acessa(l, i);
    doc = Acessa(docs, ProxIdx(prox));
    char *tipo1 = DocTipo(doc);
    // printf("%s : %lf\n", DocTipo(doc), ProxProx(prox));
  }
  t_max = ModaDeClasse(l, docs, k);

  resultado = malloc(sizeof(char) * TYPE_SIZE);
  strcpy(resultado, t_max);
  LiberaLista(l);
  LiberaDocumento(busca_doc);

  return resultado;
}

double comparar(tDocumento_pt doc1, tDocumento_pt doc2, tListaHash_pt lh,
                int n_docs) {
  int i = 0, j = 0, controle;
  double tf1, tf2, idf, denom1 = 0, denom2 = 0, numer = 0;
  tLista_pt propPals1, propPals2;
  tPropriedadePal_pt pp1, pp2, pp;
  tPalavra_pt palavra;

  propPals1 = DocPalsFreq(doc1);
  propPals2 = DocPalsFreq(doc2);

  while (i < qtd(propPals1) || j < qtd(propPals2)) {
    if (i >= qtd(propPals1)) {
      pp = Acessa(propPals2, j);
      j++;
    } else if (j >= qtd(propPals2)) {
      pp = Acessa(propPals1, i);
      i++;
    } else {
      pp1 = Acessa(propPals1, i);
      pp2 = Acessa(propPals2, j);
      controle = strcmp(PropPalPal(pp1), PropPalPal(pp2));
      if (controle < 0) {
        pp = pp1;
        i++;
      } else if (controle > 0) {
        pp = pp2;
        j++;
      } else {
        pp = pp1;
        i++;
        j++;
      }
    }

    tf1 = TF(doc1, PropPalPal(pp));
    tf2 = TF(doc2, PropPalPal(pp));

    palavra = ObtemPalavraDeListaHash(lh, PropPalPal(pp));
    if (palavra)
      idf = IDF(qtd(PalProps(palavra)) + 1, n_docs + 1);
    else
      idf = IDF(1, n_docs + 1);

    denom1 += tf1 * tf1 * idf * idf;
    denom2 += tf2 * tf2 * idf * idf;
    numer += tf1 * tf2 * idf * idf;
  }

  return numer / (sqrt(denom1) * sqrt(denom2));
}

tLista_pt AparicoesDePalavraEmDocumento(tLista_pt docs, tPalavra_pt p) {
  int i;
  tPropriedadeDoc_pt pd;
  tDocumento_pt d;
  tTipo_pt t;
  tLista_pt propsPalavra = PalProps(p);
  tLista_pt propsCpy = CriaCopiaDeLista(propsPalavra);
  OrdenaLista(propsCpy, CompFreq);

  tLista_pt ClasseEFreqNosDocs = InicializaLista(qtd(propsPalavra), TIPO);
  printf("A palavra '%s' aparece em %d documentos\n", PalavraPal(p),
         qtd(propsPalavra));

  for (i = 0; i < qtd(propsPalavra); i++) {
    pd = Acessa(propsCpy, i);
    d = Acessa(docs, PropDocIdx(pd));
    t = NovoTipo(DocTipo(d), PropDocFreq(pd));
    ClasseEFreqNosDocs = add(ClasseEFreqNosDocs, t);
    if (i < PRTQTD)
      printf("\t%d vezes no documento %d\n", PropDocFreq(pd), PropDocIdx(pd));
  }
  LiberaCopiaDeLista(propsCpy);
  return ClasseEFreqNosDocs;
}

void AparicoesDePalavraPorClasse(tLista_pt ClasseEFreqNosDocs) {
  tLista_pt contagem = InicializaLista(qtd(ClasseEFreqNosDocs), TIPO);
  int n, i;
  tTipo_pt t;
  printf("Em cada classe\n");

  OrdenaLista(ClasseEFreqNosDocs, CompTipo);

  ContagemEmLista(contagem, ClasseEFreqNosDocs, CompTipo, NovoVoidTipo,
                  VoidTipoFreq, VoidTipoClasse);
  OrdenaLista(contagem, CompFreqTipo);

  n = qtd(contagem) < PRTQTD ? qtd(contagem) : PRTQTD;
  for (i = 0; i < n; i++) {
    t = Acessa(contagem, i);
    printf("\t%d vezes na classe %s\n", TipoFreq(t), TipoClasse(t));
  }
  LiberaLista(contagem);
}

void RelatorioDePalavras(char *palavra, tListaHash_pt lh, tLista_pt docs) {
  tLista_pt ClasseEFreqNosDocs;
  tPalavra_pt p = ObtemPalavraDeListaHash(lh, palavra);

  if (p == NULL) {
    printf("Palavra %s não encontrada em nenhum documento\n\n", palavra);
    return;
  }

  ClasseEFreqNosDocs = AparicoesDePalavraEmDocumento(docs, p);

  if (qtd(ClasseEFreqNosDocs))
    AparicoesDePalavraPorClasse(ClasseEFreqNosDocs);

  printf("\n");
  LiberaLista(ClasseEFreqNosDocs);
}

void RelatorioDeDocumentos(tLista_pt docs) {
  int n, i;
  tDocumento_pt d;
  tLista_pt docsCpy;
  docsCpy = CriaCopiaDeLista(docs);
  OrdenaLista(docsCpy, CompDocTamCres);

  printf("%d maiores documentos:\n", PRTQTD);
  n = qtd(docsCpy) < PRTQTD ? qtd(docsCpy) : PRTQTD;
  for (i = 0; i < n; i++) {
    d = Acessa(docsCpy, i);
    printf("\tDocumento %d da classe %s com %d palavras\n", DocIdx(d),
           DocTipo(d), DocNPals(d));
  }
  OrdenaLista(docsCpy, CompDocTamDec);
  printf("%d menores documentos:\n", PRTQTD);

  for (i = 0; i < n; i++) {
    d = Acessa(docsCpy, i);
    printf("\tDocumento %d da classe %s com %d palavras\n", DocIdx(d),
           DocTipo(d), DocNPals(d));
  }
  printf("\n");
  LiberaCopiaDeLista(docsCpy);
}

tListaHash_pt AbrirListaHash(const char *filename) {
  FILE *arq = fopen(filename, "rb");

  if (arq == NULL) {
    printf("ABRIR L-HASH | Nao foi possivel abrir o arquivo\n");
    exit(EXIT_FAILURE);
  }

  tPalavra_pt PalAtual;
  tPropriedadeDoc_pt PropAtual;
  float TF_IDF;
  int index, freq, i, J, K, LHSize = 0, QTD_Hash = 0, QTD_IT_ListaAtual = 0,
                            QTD_Palavras = 0, STR_size = 0, QTD_Props = 0;
  char *string_atual = (char *)malloc(sizeof(char));

  fread(&LHSize, sizeof(int), 1, arq);
  fread(&QTD_Hash, sizeof(int), 1, arq);

  tListaHash_pt ListaHashAtual = InicializaListaHash(LHSize);

  for (i = 0; i < QTD_Hash; i++) {
    fread(&QTD_IT_ListaAtual, sizeof(int), 1, arq);

    for (J = 0; J < QTD_IT_ListaAtual; J++) {
      fread(&STR_size, sizeof(int), 1, arq);
      string_atual = (char *)realloc(string_atual, STR_size + 1);
      fread(string_atual, sizeof(char), STR_size + 1, arq);
      PalAtual = NovaPalavra(string_atual);

      fread(&QTD_Props, sizeof(int), 1, arq);

      for (K = 0; K < QTD_Props; K++) {

        fread(&index, sizeof(int), 1, arq);
        fread(&freq, sizeof(int), 1, arq);
        fread(&TF_IDF, sizeof(float), 1, arq);

        PropAtual = NovaPropDoc(index, freq);
        SetPropDocTFIDF(PropAtual, TF_IDF);

        addProp(PalAtual, PropAtual);
      }
      addHash(ListaHashAtual, PalAtual);
    }
  }

  fclose(arq);
  free(string_atual);
  return ListaHashAtual;
}

tLista_pt AbrirListaDocumento(const char *filename) {
  FILE *arq = fopen(filename, "rb");
  if (arq == NULL) {
    printf("ABRIR L-DOCS | Nao foi possivel abrir o arquivo\n");
    exit(EXIT_FAILURE);
  }
  tLista_pt Documentos, Propriedades;
  int i, J, freq, TamTipo, TamConteudo, TamPPalConteudo, TamLista, TamCaminho,
      QTD_Props = 0;
  char esc = '\0', *Conteudo, *Tipo, *PropPal, *caminho = NULL;

  tDocumento_pt DocumentoAtual;
  tPropriedadePal_pt PropAtual;

  fread(&TamLista, sizeof(int), 1, arq);
  Documentos = InicializaLista(TamLista, DOCUMENTO);
  for (i = 0; i < TamLista; i++) {
    Tipo = malloc(sizeof(char) * (TYPE_SIZE));
    fread(Tipo, sizeof(char), TYPE_SIZE, arq);
    fread(&TamConteudo, sizeof(int), 1, arq);

    fread(&TamCaminho, sizeof(int), 1, arq);
    caminho = malloc(sizeof(char) * (TamCaminho + 1));
    fread(caminho, sizeof(char), TamCaminho, arq);
    caminho[TamCaminho] = '\0';

    DocumentoAtual =
        InicializaNovoDocumento(i, NULL, TamConteudo, Tipo, caminho);
    free(Tipo);

    Propriedades = DocPalsFreq(DocumentoAtual);
    fread(&QTD_Props, sizeof(int), 1, arq);

    for (J = 0; J < QTD_Props; J++) {
      fread(&TamPPalConteudo, sizeof(int), 1, arq);
      PropPal = malloc(sizeof(char) * (TamPPalConteudo + 1));
      fread(PropPal, sizeof(char), TamPPalConteudo, arq);
      PropPal[TamPPalConteudo] = '\0';

      fread(&freq, sizeof(int), 1, arq);
      PropAtual = NovaPropPal(PropPal, freq);
      Propriedades = add(Propriedades, PropAtual);
      free(PropPal);
    }
    Documentos = add(Documentos, DocumentoAtual);
  }

  fclose(arq);
  return Documentos;
}