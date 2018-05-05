#include <stdio.h>
#include <stdlib.h>

const char SKIP_CHAR = ' ';

int my_strlen_word(char *str, char sep) {
    int i = 0;
    
    while (str[i] != sep && str[i] != '\0')
        ++i;
    return i;
}

char *my_strdup(const char *src) {
  int length = my_strlen_word(src, SKIP_CHAR);
  char *dst = malloc(sizeof(char) * length + 1);

  if (dst == NULL)
    return NULL;
  for(int i = 0; i < length; i++) {
    dst[i] = src[i];
  }  
  dst[length] = '\0';
  return dst;
}

int my_count_words(char *sentence) {
    int length = 0;
    int count = 0;
    char previousChar = SKIP_CHAR;
    char current = '\0';
    
    while(sentence[length] != '\0') {
        current = sentence[length];
        if (current == SKIP_CHAR && sentence[length] != previousChar) {
            count++;
        }
        previousChar = current;
        length++;
    }
    if (length == 0) {
        return 0;  
    } else if (current != SKIP_CHAR) {
        return count + 1;
    } else {
        return count;
    }
}

char *next_word(char *str, char sep) {
    int i = 0;

    while (str[i] == sep && str[i] != '\0') // skip sep
        ++i;
    return str + i;
}

// "hello world" -> ["hello", "world"]
// "hello" -> ["hello"]
// "" -> []
char **my_split(const char *src) {
    char *str = my_strdup(src);
    int *result = malloc(my_count_words(src) * sizeof(int));
    int resultIndex = 0;
    
    if (str == NULL || result == NULL)
        return NULL;
    while(str[0] != '\0') {
        if (str[0] == SKIP_CHAR) {
            str = next_word(str, SKIP_CHAR);
        } else {
            int length = my_strlen_word(str, SKIP_CHAR);
            
            result[resultIndex] = str;
            str += result[length];
            resultIndex++;
        }
    }
    return result;
    }

int main() {

    char **result = my_split("hellow world");
    
    if (result != NULL) {
        for (int i = 0; i < 2; i++)
            printf("%s\n", result[i]);
        free(result);
    }
    
    return 0;
}