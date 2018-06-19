#include <stdio.h>
#include <unistd.h>
#include <signal.h>

#define MAX_INPUT_CHAR_LENGTH 128

// basic shell
// readline -> execute command with args or builtin function in a separate process

// builtin function
// setenv/unsetenv/env/cd

// man <cmd> for more information
// fork/vfork
// execve
// chdir
// calloc/malloc/free
// lstat/stat

// 1. step 
// readline -> execute command using execve and fork

// 2.
// setenv/unsetenv/env
//

// 3.
// cd using chdir
// cd 
// cd /vsv 
// cd ./vdfvs 
// cd toto cd ../
// cd -

/*
start point
int main(int ac, char **av, char **env) {

}
*/


//signal
//exit
//read/write
//fork/vfork
//execve
//chdir
//stat/lstat
//malloc/free/calloc
int my_strlen(char *str) {
  int len = 0;
  while (str[len])
    len++;
  return len;
}

int my_puts(char *str) {
  return write(1, str, my_strlen(str));
}

void catch_signal(int ignored) {
  my_puts("catch signal");
}

int my_index_of(char find, char *str) {
  int index = 0;

  while(str) {
    if (str[index] == find)
      return index;
  }
  return -1;
}
// dfbdfbdfbdfsbbnfaionbofinbiofnbofsnboisfnbnfbonsfoibns\ndvvsvbdfbfdbsdbbdfbs\n
// dfbdfbdfbdfsbbnfaionbofinbiofnbofsnboisfnbnfbonsfoibns\n
// 
char *read_line(void) {
  static char buffer[1024];
  static int position = 0;
  int length = 0;
  // char *result = malloc(sizeof(char) * length + 1);

  if (buffer[0] == '\0') {
    length = read(0, buffer, 1024);
    if (length == 0)
      return NULL;
    if (length < 0)
      return NULL;
  }

  whle (my_index_of('\n', buffer) == -1) {
    // no newline
  }
  
  // while (buffer[0] == '\0') {

  // }

  return ;
}

int main() {
  int status = 0;
  // char *line = NULL;

  // signal(2, &catch_signal);
  while(status == 0) {
    my_puts("> ");
    // sample();
    read_line();
    // split command, args
    // exec
  }
  return status;
}
