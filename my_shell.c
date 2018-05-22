#include <stdio.h>
#include <stdlib.h>

#define MAX_INPUT_CHAR_LENGTH 128

char *read_line(void) {
  char temp[MAX_INPUT_CHAR_LENGTH];
  char c = '\0';
  int position = 0;

  while(c != '\n') {
    if (position == MAX_INPUT_CHAR_LENGTH) {
      printf("Max size error");
      return NULL;
    }
    c = getchar();
    temp[position++] = c;
  }

  char *line = malloc(sizeof(char) * position + 1);

  if (line == NULL) {
    printf("Memory allocation error");
    return NULL;
  }
  for(int i = 0; i < position; i++)
    line[i] = temp[i];
  line[position] = '\0';
  return line;
}

int main() {
  int status = 0;
  char *line = NULL;

  while(status == 0) {
    printf("> ");
    line = read_line();
    if (line == NULL)
      return 1;
  }
  return status;
}
