/*
Compile: make list_operations
Run: ./list_operations
Compile & run: make list_operations && ./list_operations
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct DoubleNode {
    double value;
    struct DoubleNode *next;
} DoubleNode;

typedef struct DoubleList {
    DoubleNode *first;
    DoubleNode *last;
} DoubleList;

DoubleList *new_list(void) {
    return calloc(1, sizeof(DoubleList));
}

DoubleNode *new_node(double value) {
    // todo: implement
    return NULL;
}

void print(DoubleList *list) {
    printf("[");
    for (DoubleNode *node = list->first; node != NULL; node = node->next) {
        printf("%f ", node->value);
    }
    printf("]\n");
}

void append(DoubleList *list, double value) {
    // todo: implement
}

void free_list(DoubleList *list) {
    // todo: implement
}

double sum(DoubleList *list) {
    // todo: implement
    return 0.0;
}

double max_element(DoubleList *list) {
    // todo: implement
    return 0.0;
}

int number_of_sign_changes(DoubleList *list) {
    // todo: implement
    return 0;
}

DoubleList *list_of_string(char *s) {
    DoubleList *list = new_list();
    char *t = s;
    char *endp;
    while (*t != '\0') {
        if (isdigit(*t)) {
            if (t > s && *(t - 1) == '.') t--; // check for '.'
            if (t > s && *(t - 1) == '-') t--; // check for '-'
            append(list, strtod(t, &endp)); // convert digit string to int
            t = endp;
        } else {
            // assert: *t is not a digit, *t is not '\0'
            t++; // not a digit, skip
        }
    }
    return list;
}

int sum_test() {
    DoubleList *list = list_of_string("0");
    double x = sum(list);
    free_list(list);
    if (x != 0) return 1;
    
    list = list_of_string("1, 11");
    x = sum(list);
    free_list(list);
    if (x != 12) return 2;
    
    list = list_of_string("1, -11");
    x = sum(list);
    free_list(list);
    if (x != -10) return 3;
    
    list = list_of_string("2, 1, -2");
    x = sum(list);
    free_list(list);
    if (x != 1) return 4;
    
    list = list_of_string("4, -1, 2, -3, 4");
    x = sum(list);
    free_list(list);
    if (x != 6) return 5;
    
    list = list_of_string("7, -1, 1, 2, -1, -1, -1, 2");
    x = sum(list);
    free_list(list);
    if (x != 8) return 6;
    
    return 0;
}

int max_element_test() {
    DoubleList *list = list_of_string("0");
    double x = max_element(list);
    free_list(list);
    if (x != 0) return 1;
    
    list = list_of_string("1, 11");
    x = max_element(list);
    free_list(list);
    if (x != 11) return 2;
    
    list = list_of_string("1, -11");
    x = max_element(list);
    free_list(list);
    if (x != 1) return 3;
    
    list = list_of_string("2, 1, -2");
    x = max_element(list);
    free_list(list);
    if (x != 2) return 4;
    
    list = list_of_string("4, -1, 2, -3, 4");
    x = max_element(list);
    free_list(list);
    if (x != 4) return 5;
    
    list = list_of_string("7, -1, 1, 2, -1, -1, -1, 2");
    x = max_element(list);
    free_list(list);
    if (x != 7) return 6;
    
    return 0;
}

int number_of_sign_changes_test() {
    DoubleList *list = list_of_string("0");
    int i = number_of_sign_changes(list);
    free_list(list);
    if (i != 0) return 1;
    
    list = list_of_string("1, 11");
    i = number_of_sign_changes(list);
    free_list(list);
    if (i != 0) return 2;
    
    list = list_of_string("1, -11");
    i = number_of_sign_changes(list);
    free_list(list);
    if (i != 1) return 3;
    
    list = list_of_string("2, 1, -2");
    i = number_of_sign_changes(list);
    free_list(list);
    if (i != 1) return 4;
    
    list = list_of_string("4, -1, 2, -3, 4");
    i = number_of_sign_changes(list);
    free_list(list);
    if (i != 4) return 5;
    
    list = list_of_string("7, -1, 1, 2, -1, -1, -1, 2");
    i = number_of_sign_changes(list);
    free_list(list);
    if (i != 4) return 6;
    
    return 0;
}

int main(void) {
    int i = 0;
    if ((i = sum_test()) == 0) printf("sum_test passed\n"); 
    else printf("sum_test %d failed\n", i);
    if ((i = max_element_test()) == 0) printf("max_element_test passed\n"); 
    else printf("max_element_test %d failed\n", i);
    if ((i = number_of_sign_changes_test()) == 0) printf("number_of_sign_changes_test passed\n"); 
    else printf("number_of_sign_changes_test %d failed\n", i);
    return 0;
}
