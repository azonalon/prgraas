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
    DoubleNode* new_node = malloc(sizeof(DoubleNode));
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

void print(DoubleList *list) {
    printf("[");
    for (DoubleNode *node = list->first; node != NULL; node = node->next) {
        printf("%f ", node->value);
    }
    printf("]\n");
}

void append(DoubleList* list, double value) {
    DoubleNode* n = new_node(value);
    DoubleNode* last = list->last;
    if (last != NULL) {
        last->next = n;
        list->last = n;
    }
    else {
        list->first = n;
        list->last = n;
    }
}

void free_list(DoubleList *list) {
    DoubleNode* n = list->first;
    while(n != NULL) {
        DoubleNode* next = n->next;
        free(n);
        n = next;
    }
    free(list);
}

double sum(DoubleList *list) {
    double sum = 0.0;
    DoubleNode* n = list->first;

    while(n != NULL) {
        sum += n->value;
        n = n->next;
    }
    return sum;
}

double max_element(DoubleList *list) {
    double max = -1.0/0.0;
    // negative infinity

    DoubleNode* n = list->first;

    while(n != NULL) {
        if(n->value > max) {
            max = n->value;
        }
        n = n->next;
    }
    return max;
}

int number_of_sign_changes(DoubleList *list) {
    int sign_changes = 0;

    DoubleNode* n = list->first;
    while(n->next != NULL) {
        if(n->value * n->next->value < 0) {
            sign_changes++;
        }
        n = n->next;
    }
    return sign_changes;
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
