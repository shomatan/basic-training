#include <stdio.h>
#include <stdlib.h>

const char SKIP_CHAR = ' ';

int my_strlen_word(const char *str, char sep) {
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

int my_count_words(const char *sentence) {
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

char *next_word(const char *str, char sep) {
    int i = 0;

    while (str[i] == sep && str[i] != '\0') // skip sep
        ++i;
    return (char*)str + i;
}

char *sub_string(const char *str, int index, int length) {
    char *word = malloc(length * sizeof(str) + 1);

    if (word == NULL)
        return NULL;
    for (; index < length; ++index) 
        word[index] = str[index];
    word[length] = '\0';
    return word;    
}

void free_2d_string(void **array) {
    for (int i = 0; array[i]; ++i)
        free(array[i]);
    free(array);
}

// "hello world" -> ["hello", "world"]
// "hello" -> ["hello"]
// "" -> []
char **my_split(const char *src) {
    char *str = (char*)src;
    int wordsCount = my_count_words(str);
    int resultIndex = 0;
    char **result = calloc(wordsCount + 1, sizeof(str));
    char *word = NULL;
    int length = 0;

    if (result == NULL) 
        return NULL;
    while (str[0]) {
        if (str[0] == SKIP_CHAR) {
            str = next_word(str, SKIP_CHAR);
        } else {
            length = my_strlen_word(str, SKIP_CHAR); // 5
            word = sub_string(str, 0, length);

            if (word == NULL) {
                free_2d_string((void**)result);
                return NULL;
            }
            result[resultIndex++] = word;
            str = str + length;
        }
    }
    result[wordsCount] = NULL;
    return result;
}

int main() {
    
    char **result = my_split("            hello            world !!     test AASSDDEFFV             cxvcxdsgsdgsd                    fbbdsbfdbdfbdf       ");
    
    if (result != NULL) {
        for (int i = 0; result[i]; i++) {
            printf("%s\n", result[i]);
        }
        free_2d_string((void**)result);
    }
    
    return 0;
}
