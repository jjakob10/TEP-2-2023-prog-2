#include "../Headers/utils.h"

char *str_trim_malloc_cpy(char *str2) {
  int i, offset, len = strlen(str2);
  char *str1, *temp = malloc((len + 1) * sizeof(char));
  strcpy(temp, str2);

  // Retira espaços depois
  for (i = len - 1; (isspace(temp[i])); i--)
    ;

  // Retira espaçoes antes
  for (offset = 0; isspace(*(temp + offset)); offset++)
    ;

  // Reposiciona fim da string
  temp[i + 1] = '\0';

  // Aloca uma nova string e copia uma versão modificada da string
  str1 = malloc((strlen(temp + offset) + 1) * sizeof(char));
  strcpy(str1, temp + offset);
  free(temp);
  return str1;
}

void str_trim_cpy(char *str1, char *str2) {
  int i, offset, len = strlen(str2);
  char *temp = malloc((len + 1) * sizeof(char));
  strcpy(temp, str2);

  // Retira espaços depois
  for (i = len - 1; (isspace(temp[i])); i--)
    ;

  // Retira espaços antes
  for (offset = 0; isspace(*(temp + offset)); offset++)
    ;

  temp[i + 1] = '\0';

  // Copia uma versão modificada da string em um espaço dado
  strcpy(str1, temp + offset);
  free(temp);
}

char *toLowerStr(char *str) {
  char *pt;
  for (pt = str; *pt; pt++)
    *pt = tolower(*pt);
  return str;
}

char *Concatenar(const char *str1, const char *str2, const char *str3) {
  char *Concatenar = (char *)malloc(
      sizeof(char) * (strlen(str1) + strlen(str2) + strlen(str3) + 1));
  strcpy(Concatenar, str1);
  strcat(Concatenar, str2);
  strcat(Concatenar, str3);
  return Concatenar;
}

tLista_pt StrToPropPalList(char *string) {
  tLista_pt Palavras = InicializaLista(TAMLISTA, PROPRIEDADEPAL);

  tPropriedadePal_pt p = NULL;
  char *save = NULL, *token = NULL, *str = NULL;
  str = str_trim_malloc_cpy(string);
  token = strtok_r(str, " ", &save);
  while (token != NULL) {
    p = NovaPropPal(token, 0);
    Palavras = add(Palavras, p);
    token = strtok_r(NULL, " ", &save);
  }
  free(str);
  return Palavras;
}

int ReturnOne(void *i) { return 1; }

char *RemoveExtention(char *str) {
  char *strcpy = str_trim_malloc_cpy((char *)str);
  char *ext = strrchr(str, '.');
  strcpy[strlen(strcpy) - strlen(ext)] = '\0';
  return strcpy;
}