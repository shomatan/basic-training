#include <stdio.h>
#include <stdlib.h>

char *my_strdup(const char *src) {
  int length = my_strlen(src);
  char *dst = malloc(sizeof(char) * length + 1);

  if (dst == NULL)
    return NULL;
  for(int i = 0; i < length; i++) {
    dst[i] = src[i];
  }  
  dst[length] = '\0';
  return dst;
}