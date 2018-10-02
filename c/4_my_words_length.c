#include <stdio.h>
#include <stdlib.h>

static const char SKIP_CHAR = ' ';

int my_count_words(char *sentence) {
    int length = 0;
    int count = 0;
    char previousChar = SKIP_CHAR;
    char current = '\0';
    
    while(sentence[length] != '\0') {
        current = sentence[length];
        if (current == SKIP_CHAR && sentence[length] != previousChar)
            count++;
        previousChar = current;
        length++;
    }
    if (length == 0)
        return 0;  
    else if (current != SKIP_CHAR)
        return count + 1;
    return count; 
}

int my_strlen_word(char *str, char sep) {
    int i = 0;
    
    while (str[i] != sep && str[i] != '\0')
        ++i;
    return i;
}

char *next_word(char *str, char sep) {
    int i = 0;

    while (str[i] == sep && str[i] != '\0') // str[i] != '\0' <- not empty
        ++i;
    return str + i;
}

int *words_length(char *str) {
    int *result = malloc(my_count_words(str) * sizeof(int));
    int resultIndex = 0;

    if (result == NULL)
        return NULL;
    while(str[0] != '\0') {
        if (str[0] == SKIP_CHAR) {
            str = next_word(str, SKIP_CHAR);
        } else {
            result[resultIndex] = my_strlen_word(str, SKIP_CHAR);
            str += result[resultIndex];
            resultIndex++;
        }
    }
    return result;
}

int main(void){
    int *result = words_length("Hello   world in C"); // return [5, 5, 2, 1]
    
    if (result != NULL) {
        for (int i = 0; i < 4; i++)
            printf("%d\n", result[i]);
        free(result);
    }
    return 0;
}
