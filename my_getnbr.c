#include <stdio.h>
#include <stdlib.h>

int my_strlen(const char *str) {
  int size = 0;
  while(str[size] != '\0') {
    size++;
  }
  return size;
}

// 2^3 = 2 * 2 * 2
int my_power_rec(int x, int n) {
    if (n == 0) {
        return 1;
    } else {
        return x * my_power_rec(x, n - 1);
    }
}

// 12345678 = 1 * 10^7 + 2 * 10^6 + 3 * 10^5 ...

// string base -> integer 
// 101011 "01" -> 43
// AFE "0123456789ABCDEF"
// PANDA "ANPD"
// 123 "0123456789"
// ---123 "0123456789" -> -123
// ----123 "012345679" -> 123
int my_getnbr(char *str, char *base) {
  int baseLength = my_strlen(base);
  int length = my_strlen(str) - 1;
  int result = 0;
  int minusCount = 0;
  
  for (int i = 0; i < str[i]; i++) {
    for (int baseIndex = 0; baseIndex < baseLength; baseIndex++) {
      if (str[i] == base[baseIndex]) {
        printf("%c * %d^%d\n", str[i], baseLength, length);
        result += baseIndex * my_power_rec(baseLength, length);
        length--;
        break;
      } else if (str[i] == '-') {
        minusCount++;
        length--;
        break;
      }
    }
  }
  return result * my_power_rec(-1, minusCount);
}

int main() {
  printf("%d\n", my_getnbr("--1111", "01")); // 15
  printf("%d\n", my_getnbr("---1111", "01")); // -15
  return 0;
}