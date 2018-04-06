#include <stdio.h>
#include <stdlib.h>

int my_strlen(const char *str) {
  int size = 0;
  while(str[size] != '\0') {
    size++;
  }
  return size;
}