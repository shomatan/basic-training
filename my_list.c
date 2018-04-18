#include <stdio.h>
#include <stdlib.h>

struct s_list {
    int value;
    struct s_list *next;
};

struct s_list *prepend(struct s_list *list, int value) {
    struct s_list *newElem = malloc(sizeof(*list));

    newElem->value = value;
    newElem->next = NULL;
    if (list == NULL) {
        return newElem;
    }
    newElem->next = list;
    return newElem;
}

int list_length(struct s_list *list) {
    if (list == NULL) {
        return 0;
    }
    return list_length(list->next) + 1;
}

int main() {
    struct s_list *list = NULL;

   list = prepend(list, 1);
   list = prepend(list, 2);
   list = prepend(list, 3);
   
   list_length(NULL);
   printf("%d\n", list_length(list));
   //print
   //3
   //2
   //1
   while(list) {
       printf("%d\n", list->value);
       list = list->next;
   }
}