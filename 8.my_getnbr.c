#include <stdio.h>
#include <stdlib.h>

int my_strlen(const char *str) {
  int size = 0;
  while (str[size])
    ++size;
  return size;
}

// 2^3 = 2 * 2 * 2
int my_power_rec(int x, int n) {
  if (n == 0)
    return 1;
  return x * my_power_rec(x, n - 1);
}

int str_index_of(char c, char *str) {
  for (int i = 0; str[i]; ++i)
    if (str[i] == c)
      return i;
  return -1;
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
  int length = 0;
  int result = 0;
  int multiplier = 1;
  int i = 0;
  int nb = -1;
  
  while (str[i] == '+' || str[i] == '-') {
    if (str[i] == '-')
      multiplier *= -1;
    ++i;
  }
  length = my_strlen(str + i) - 1;
  for (; str[i]; i++) {
    nb = str_index_of(str[i], base);
    if (nb != -1) {
      result += nb * my_power_rec(baseLength, length);
      --length;
    } else
      return 0;
  }
  return result * multiplier;
}

int main() {
  printf("%d\n", my_getnbr("--1111", "01")); // 15
  printf("%d\n", my_getnbr("+++---1111", "01")); // -15
  return 0;
}
