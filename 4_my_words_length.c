#include <stdio.h>
#include <stdlib.h>

struct List {
    int value;
    struct List *next;
};

struct List *last(struct List *list) {
    if (list == NULL)
        return NULL;
        
    struct List *item = list;
    
    while (item->next) {
        item = item->next;
    }
    return item;
}

struct List *append(struct List *list, int value) {
    struct List *newElem = malloc(sizeof(*list));
    
    newElem->value = value;
    newElem->next = NULL;
    if (list == NULL) {
        return newElem;
    }
    
    struct List *lastItem = last(list);
    
    if (lastItem == NULL) {
        list->next = newElem;
        return list;
    }
    
    lastItem->next = newElem;
    return list;
}

int count(struct List *list) {
    if (list == NULL)
        return 0;
        
    struct List *item = list;
    int count = 1;
    
    while (item->next) {
        item = item->next;
        count++;
    }
    return count;
}

int *words_length(char *str) {
    
    const char SKIP_CHAR = ' ';

    int length = 0;
    int wordCount = 0;
    char current = NULL;
    struct List *lengthList = NULL;
    
    while(str[length] != '\0') {
        current = str[length];
        if (current == SKIP_CHAR) {
            if (count > 0) {
                lengthList = append(lengthList, wordCount);
            }
            wordCount = 0;
        } else {
            wordCount++;
        }
        length++;
    }
    
    if (wordCount > 0) {
        lengthList = append(lengthList, wordCount);
    }
    
    int listCount = count(lengthList);
    
    if (listCount > 0) {
        int *result = malloc(listCount * sizeof(int));
        struct List *item = lengthList;
        struct List *temp = NULL;
        int i = 0;
        
        while(item) {
            result[i] = item->value;
            temp = item;
            item = item->next;
            free(temp);
            i++;
        } 
        return result;
    } else {
        return NULL;
    }
}

int main(void){
    
    int *result = words_length("Hello world in C"); // return [5, 5, 2, 1]
    
    for (int i = 0; i < 4; i++) {
        printf("%d\n", result[i]);
    } 
    
}
