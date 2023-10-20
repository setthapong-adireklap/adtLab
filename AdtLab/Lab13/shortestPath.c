#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int nodeNum;
    int lenght;
    char visited;
} node_t;

typedef struct nodeQ{
    node_t *node;
    struct nodeQ *next; 
} queue_t;

queue_t *createQueue(node_t *node){
    queue_t *nodeQ = (queue_t*)malloc(sizeof(queue_t));
    nodeQ->node = node;
    nodeQ->next = NULL;
    return nodeQ;
}

queue_t *enqueue(queue_t *q, node_t *node){
    queue_t *temp = q;
    while(temp->next != NULL){
        temp = temp->next;
    }
    temp->next = createQueue(node);
    return q;
}

queue_t *dequeue(queue_t *q){
    queue_t *temp = q;
    q = q->next;
    free(temp);
    return q;
}

node_t *createNode(int num){
    node_t *node = (node_t*)malloc(sizeof(node_t));
    node->lenght = -1;
    node->nodeNum = num;
    node->visited = '0';
    return node;
}

node_t **createNodeArr(int n){
    node_t **nodeArr = (node_t**)malloc(n*sizeof(node_t*));
    for(int i = 0 ; i<n ; i++){
        nodeArr[i] = createNode(i);
    }
    return nodeArr;
}

void resetNode(node_t **nodeArr,int n){
    for(int i = 0 ; i<n ;i++){
        nodeArr[i]->lenght = -1;
        nodeArr[i]->visited = '0';
    }
}   

int shortPath(int a, int b, int n, int** arr, node_t **nodeArr){
    
    if(a == b){
        return 0;
    }
    
    nodeArr[a]->lenght = 0;
    nodeArr[a]->visited = '1';
    queue_t *start = createQueue(nodeArr[a]); 

    while(start != NULL){
        for(int i = 0 ; i<n ; i++){
            if(arr[start->node->nodeNum][i] != 0){
                if(nodeArr[i]->visited == '0'){
                    start = enqueue(start,nodeArr[i]);
                    nodeArr[i]->visited = '1';
                }
                if(nodeArr[i]->lenght == -1){
                    nodeArr[i]->lenght = start->node->lenght + arr[start->node->nodeNum][i];
                }
                else if(nodeArr[i]->lenght != -1 && nodeArr[i]->lenght > (start->node->lenght + arr[start->node->nodeNum][i])){
                    start = enqueue(start,nodeArr[i]);
                    nodeArr[i]->lenght = start->node->lenght + arr[start->node->nodeNum][i];
                }
            }
        }
        start = dequeue(start);
    }
    return nodeArr[b]->lenght;
}

int main(){

    int n, m, p;
    scanf("%d %d %d", &n, &m, &p);

    int **arr = calloc(n,sizeof(int*));
    for(int i = 0 ; i<n ; i++){
        arr[i] = calloc(n,sizeof(int));
    }
    node_t **nodeArr = createNodeArr(n);

    int temp1, temp2, temp3;
    for(int i = 0 ; i<m ; i++){
        scanf("%d %d %d", &temp1, &temp2, &temp3);
        arr[temp1][temp2] = temp3;
        arr[temp2][temp1] = temp3;
    }

    int a,b;
    for(int i = 0 ; i<p ; i++){
        scanf("%d %d", &a, &b);
        printf("%d\n",shortPath(a,b,n,arr,nodeArr));
        resetNode(nodeArr,n);
    }

    for(int i = 0 ; i<n ; i++){
        free(nodeArr[i]);
        free(arr[i]);
    }
    free(nodeArr);
    free(arr);
   
    return 0;
}