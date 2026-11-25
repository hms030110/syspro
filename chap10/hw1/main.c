#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

void push(struct node **top, int data) {
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    if (newNode == NULL) {
        perror("malloc");
        exit(1);
    }
    newNode->data = data;
    newNode->next = *top;
    *top = newNode;
}

int pop(struct node **top) {
    if (*top == NULL) {
        return -1;
    }
    struct node *temp = *top;
    int data = temp->data;
    *top = (*top)->next;
    free(temp);
    return data;
}

int main() {
    struct node *top = NULL;
    double input;

    while (scanf("%lf", &input) == 1) {
        if (input <= 0 || input != (int)input) {
            break;
        }
        push(&top, (int)input);
    }

    printf("Print stack\n");
    while (top != NULL) {
        printf("%d\n", pop(&top));
    }

    return 0;
}
