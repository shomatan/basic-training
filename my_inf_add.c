#include <stdio.h>
#include <stdlib.h>

int my_strlen(const char *str) {
  int size = 0;
  while(str[size] != '\0')
    size++;
  return size;
}

int my_max(int n1, int n2) {
  if (n1 < n2)
    return n2;
  return n1;
}

char *my_inverse(const char *src) {
  int length = my_strlen(src);
  char *dst = malloc(sizeof(char) * length + 1);

  if (dst == NULL)
    return NULL;
  for (int i = 0; i < length; i++) {
    dst[i] = src[length - i - 1];
  }
  dst[length] = '\0';
  return dst;
}

int my_ctoi(char c) {
  switch (c) {
	  case '0': return 0;
	  case '1': return 1;
	  case '2': return 2;
	  case '3': return 3;
	  case '4': return 4;
	  case '5': return 5;
	  case '6': return 6;
	  case '7': return 7;
	  case '8': return 8;
	  case '9': return 9;
	  default: return 0;
  }
}

// "222222" + "222222" = "444444"
// "11111000000000000000000000000000000000000000000000000000002" + "2222222222222222222222222222222233333333333333333333333" 
// "222222222222222222222222222222222222222222222222222222222222222222222222222"" + "2222222222222222222222222222222222222222222222222"
//  19����������������
// + 1
//-----
//   
// -----++++--111223 + ---1122344
// 
char *my_inf_add(char *s1, char *s2) {
  int s1Length = my_strlen(s1);
  int s2Length = my_strlen(s2);
  int length = my_max(s1Length, s2Length);
  char *s1Inversed = my_inverse(s1);
  char *s2Inversed = my_inverse(s2);
  int number = 0;
  int sum = 0;
  char *result = malloc(sizeof(char) * length + 1);
  
  if (s1Inversed == NULL) {
    if (s2Inversed != NULL)
      free(s2Inversed);
    return NULL;
  }
  if (s2Inversed == NULL)
    return NULL;
  for (int i = 0; i < length; i++) {
    sum = number + my_ctoi(s1Inversed[i]) + my_ctoi(s2Inversed[i]);
    if (sum >= 10) {
      number = 1;
      result[i] = (char)(sum - 10);
    } else {
      number = 0;
      result[i] = (char)sum;
    }
    printf("%d", sum);
  }
  
  // char *resultInversed = my_inverse(result);

  result[length] = '\0';
  return result;
}

int main() {
  char *result = my_inf_add("222222", "222222");
 
  if (result != NULL) {
    for (int i = 0; result[i]; i++) {
      printf("%c", result[i]);
    }
    free(result);
  }
  return 0;
}
