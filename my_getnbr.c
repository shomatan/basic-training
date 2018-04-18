#include <stdio.h>
#include <stdlib.h>

int my_strlen(const char *str) {
  int size = 0;
  while(str[size] != '\0') {
    size++;
  }
  return size;
}

// string base -> integer 
// 101011 "01" -> 43
// AFE "0123456789ABCDEF"
// PANDA "ANPD"
// 123 "0123456789"
// ---123 "0123456789" -> -123
// ----123 "012345679" -> 123
int my_getnbr(char *str, char *base) {
  int baseLength = my_strlen(base);
  int inputLength = my_strlen(str);
  int result = 0;

  for(int i = 0; i < inputLength; i++) {
    for(int j = 0; j < baseLength; j++) {
        if(str[i] == base[j])
    }
  }

  return 0;
}