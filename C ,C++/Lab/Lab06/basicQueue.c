#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} node_t;
typedef node_t queue_t;

void empty(queue_t *q){
    if(q == NULL){
        printf("Queue is empty.\n");
    }
    else{
        printf("Queue is not empty.\n");
    }
}

void size(queue_t *q){
    int size = 0;
    while(q!=NULL){
        q = q->next;
        size++;
    }
    printf("%d\n", size);
}

void show(queue_t *q){
    if(q==NULL){
        printf("Queue is empty.");
    }
    while(q!=NULL){
        printf("%d ", q->data);
        q = q->next;
    }
    printf("\n");
}

queue_t *enqueue(queue_t *q, int value){

    queue_t *node = (queue_t*)malloc(sizeof(queue_t));
    node->data = value;
    node->next = NULL;

    if(q == NULL){
        return node;   
    }
    queue_t *temp = q;
    while(temp->next != NULL){
        temp = temp->next;
    }
    temp->next = node;

    return q;
}

queue_t *dequeue(queue_t *q){
    
    if(q == NULL){
        printf("Queue is empty.\n");
        return q;
    }
    printf("%d\n", q->data);
    queue_t *temp = q;
    q = q->next;
    free(temp);

    return q;
}

int main(void) {
    queue_t *q = NULL;
    int n, i, command, value;
    scanf("%d", &n);
    for (i=0; i<n; i++) {
        scanf("%d", &command);
        switch(command) {
        case 1:
            scanf("%d", &value);
            q = enqueue(q, value);
            break;
        case 2:
            q = dequeue(q);
            break;
        case 3:
            show(q);
            break;
        case 4:
            empty(q);
            break;
        case 5:
            size(q);
            break;
        }
    }
return 0;
}