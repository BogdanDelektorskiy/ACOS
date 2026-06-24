#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

void push_back(Node **head, int value) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    new_node->data = value;
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
    } else {
        Node *curr = *head;
        while (curr->next != NULL)
            curr = curr->next;
        curr->next = new_node;
    }
}

Node *reverse_list(Node *head) {
    Node *prev = NULL;
    Node *curr = head;
    while (curr != NULL) {
        Node *next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}

void print_list(Node *head) {
    for (Node *curr = head; curr != NULL; curr = curr->next)
        printf("%d ", curr->data);
    printf("\n");
}

void free_list(Node *head) {
    while (head != NULL) {
        Node *tmp = head;
        head = head->next;
        free(tmp);
    }
}

int main(void) {
    Node *head = NULL;
    int num;

    printf("Enter numbers (0 to stop):\n");
    while (1) {
        scanf("%d", &num);
        if (num == 0) break;
        push_back(&head, num);
    }

    printf("Original list: ");
    print_list(head);

    head = reverse_list(head);
    printf("Reversed list: ");
    print_list(head);

    free_list(head);
    return 0;
}