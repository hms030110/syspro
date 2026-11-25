#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

void addq(struct node **head, struct node **tail, int data) {
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    if (newNode == NULL) {
        perror("malloc");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;

    if (*tail == NULL) {
        *head = newNode;
        *tail = newNode;
    } else {
        (*tail)->next = newNode;
        *tail = newNode;
    }
}

int delete(struct node **head, struct node **tail) {
    if (*head == NULL) {
        return -1;
    }
    struct node *temp = *head;
    int data = temp->data;
    *head = (*head)->next;
    if (*head == NULL) {
        *tail = NULL;
    }
    free(temp);
    return data;
}

int main() {
    struct node *head = NULL;
    struct node *tail = NULL;
    double input;

    while (scanf("%lf", &input) == 1) {
        if (input <= 0 || input != (int)input) {
            break;
        }
        addq(&head, &tail, (int)input);
    }

    printf("Print queue\n");
    while (head != NULL) {
        printf("%d\n", delete(&head, &tail));
    }

    return 0;
}
