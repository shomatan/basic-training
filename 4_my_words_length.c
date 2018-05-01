#include <stdio.h>
#include <stdlib.h>

int my_count_words(char *sentence) {

    const char SKIP_CHAR = ' ';

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

int *words_length(char *str) {
    
    const char SKIP_CHAR = ' ';

    int *result = malloc(my_count_words(str) * sizeof(int));
    
    if (result == NULL)
        return NULL;
    
    char current = '\0';
    int length = 0;
    int wordCount = 0;
    int resultIndex = 0;

    while(str[length] != '\0') {
        current = str[length];
        if (current == SKIP_CHAR) {
            if (wordCount > 0) {
                result[resultIndex] = wordCount;
            }
            wordCount = 0;
            resultIndex++;
        } else {
            wordCount++;
        }
        length++;
    }
    
    if (wordCount > 0) {
        result[resultIndex] = wordCount;
    }
    
    return result;
}

int main(void){
    
    int *result1 = words_length("Hello world in C"); // return [5, 5, 2, 1]
    
    for (int i = 0; i < 4; i++) {
        printf("%d\n", result1[i]);
    } 
    
    free(result1);
}
