#include <stdio.h>
#include <stdlib.h>

struct List {
    int value;
    struct List *next;
};

struct list *prepend(struct List *list, int value) {
    struct List *newElem = malloc(sizeof(*list));

    newElem->value = value;
    newElem->next = NULL;
    if (list == NULL) {
        return newElem;
    }
    newElem->next = list;
    return newElem;
}

struct list *append(struct List *list, int value) {
    struct List *newElem = malloc(sizeof(*list));
    
    newElem->value = value;
    newElem->next = NULL;
    if (list == NULL) {
        return newElem;
    }
    list->next = newElem;
    return list;
}

int *words_length(char *str) {
  return 0;
}

int main(void){
    
    struct List *list = NULL;

    list = append(list, 1);
    list = append(list, 2);
    list = append(list, 3);
    
    while(list) {
        printf("%d\n", list->value);
        list = list->next;
    }
    int *result = words_length("Hello world in C"); // return [5, 6, 2, 1]
    
}