#include <stdio.h>

int my_count_words(char *sentence) {
    const char SKIP_CHAR = ' ';
    int length = 0;
    int count = 0;
    char previousChar = SKIP_CHAR;
    char current = NULL;
    
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

int main() {
    printf("%d\n", my_count_words("")); // 0
    printf("%d\n", my_count_words("Hello")); // 1
    printf("%d\n", my_count_words("Hello    world blabla")); // 3
    printf("%d\n", my_count_words("   My name is    Mr. Scala  ")); // 5
    return 0;
}