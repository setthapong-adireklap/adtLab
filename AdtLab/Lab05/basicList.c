#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} node_t;

node_t *append(node_t *startNode){
    
    int appendValue;
    scanf("%d", &appendValue);
    
    node_t *pnode = (node_t*)malloc(sizeof(node_t));
    node_t *last = startNode;

    pnode->data = appendValue;
    pnode->next = NULL;

    if(startNode == NULL){
        return pnode;
    }

    while (last->next != NULL){
        last = last->next;
    }
    last->next = pnode;

    return startNode;
}

void get(node_t *startNode){
    int n;
    scanf("%d", &n);

    for(size_t i=0 ; i<n;i++){
        startNode=startNode->next;
    }

    printf("%d\n", startNode->data);
}

void show(node_t *startNode){
    if(startNode == NULL){
        printf("\n");
    }
    else{
        while(startNode->next != NULL){
            printf("%d ", startNode->data);
            startNode = startNode->next;
        }
        printf("%d\n", startNode->data);
    }
}

node_t *reverse(node_t *startNode){

    if(startNode == NULL){
        return NULL;
    }
    
    node_t *node = startNode;
    node_t *nextNode = startNode->next;
    startNode->next = NULL;

    while(nextNode!=NULL){
        startNode = nextNode;
        nextNode = startNode->next;
        startNode->next = node;
        node = startNode;
    }

    return startNode;
}

node_t *cut(node_t *startNode){
    
    int start, end;
    scanf("%d %d", &start, &end);

    node_t *node = startNode;
    node_t *nextNode = startNode->next;

    if(node->next == NULL){
        return startNode;
    }

    node_t *newStartnode = (node_t*)malloc(sizeof(node_t));
    node_t *temp = newStartnode;
    node_t *newNode = NULL;
    int i=0;
    while(node != NULL){
        if(start<=i && i<=end){
            if(i==start){
                temp->data = node->data;
                temp->next = NULL;
            }
            else{
                newNode = (node_t*)malloc(sizeof(node_t));
                newNode->data = node->data;
                newNode->next = NULL;
                while(temp->next != NULL){
                    temp = temp->next; 
                }
                temp->next = newNode;
            }
        }
        free(node);
        node = nextNode;
        if(node != NULL){                
            nextNode = node->next;
        }
        i++;
    }
    
    return newStartnode;
}

int main(void) {
    node_t *startNode;
    int n,i;
    char command;

    startNode = NULL;
    scanf("%d", &n);
    for (i=0; i<n; i++) {
        scanf(" %c", &command);
        switch (command) {
            case 'A':
                startNode = append(startNode);
                break;
            case 'G':
                get(startNode);
                break;
            case 'S':
                show(startNode);
                break;
            case 'R':
                startNode = reverse(startNode);
                break;
            case 'C':
                startNode = cut(startNode);
                break;
            default:
                break;
        }
    }

    return 0;
}