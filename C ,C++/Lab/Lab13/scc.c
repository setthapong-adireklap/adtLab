#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    char visited;
    int numNode;
} node_t;

typedef struct nodeS{
    node_t *node;
    struct nodeS *next;
} stack_t;

typedef struct arrayScc{
    int size;
    int *arr;
} arrScc;

arrScc *createArrScc(){
    arrScc *temp = (arrScc*)malloc(sizeof(arrScc));
    temp->size = 0;
    temp->arr = calloc(0,sizeof(int));
    return temp;
}

void deleteArrScc(arrScc *temp){
    free(temp->arr);
    free(temp);
}

node_t *createNode(int num){
    node_t *node = (node_t*)malloc(sizeof(node_t));
    node->numNode = num;
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

stack_t *createStack(node_t *node){
    stack_t *s = (stack_t*)malloc(sizeof(stack_t));
    s->next = NULL;
    s->node = node;
    return s;
}

void push(stack_t **s,node_t *nodeG){
    stack_t *temp = *s;
    *s = createStack(nodeG);
    (*s)->next = temp; 
}

void pop(stack_t **s){
    stack_t *temp = *s;
    *s = (*s)->next;
    free(temp);
}

void resetNode(node_t **nodeArr,int n){
    for(int i = 0 ; i<n ;i++){
        nodeArr[i]->visited = '0';
    }
}  

void findSeq(stack_t **s, node_t **nodeArr, node_t *current, int **arr, int n){
    current->visited = '1';
    for(int i = 0 ; i<n ; i++){
        if(arr[current->numNode][i] && nodeArr[i]->visited == '0'){
            findSeq(s,nodeArr,nodeArr[i],arr,n);
        }
    }
    push(s,current);
}

void findSCC(stack_t **s, node_t **nodeArr, node_t *current, int **tArr,int n, arrScc **res){
    current->visited = '1';
    for(int i = 0 ; i<n ; i++){
        if(tArr[current->numNode][i] && nodeArr[i]->visited == '0'){
            findSCC(s,nodeArr,nodeArr[i],tArr,n,res);
        }
    }
    (*res)->size++;
    (*res)->arr = (int*)realloc((*res)->arr,sizeof(int)*(*res)->size);
    (*res)->arr[(*res)->size-1] = current->numNode;
}

void display(int *arrInt, int size){
    for(int i = 0 ; i<size ; i++){
        printf("%d ", arrInt[i]);
    }
    printf("\n");
}

void insertionSort(int *arrInt, int size){
    int check;
    for(int i = 1 ; i<size ; i++){
        check = arrInt[i];
        for(int j = i ; j>0 ; j--){
            if(check < arrInt[j-1]){
                arrInt[j] = arrInt[j-1];
                arrInt[j-1] = check;
            }
            else{
                break;
            }
        }
    }
    display(arrInt,size);
}

int main(){

    int n, m;
    scanf("%d %d", &n, &m);

    int **arr = calloc(n,sizeof(int*));
    int **tArr = calloc(n,sizeof(int*));
    for(int i = 0 ; i<n ; i++){
        arr[i] = calloc(n,sizeof(int));
        tArr[i] = calloc(n,sizeof(int));
    }

    node_t **nodeArr = createNodeArr(n);
    stack_t *s = NULL;

    int temp1, temp2;
    for(int i = 0 ; i<m ; i++){
        scanf("%d %d", &temp1, &temp2);
        arr[temp1][temp2] = 1;
        tArr[temp2][temp1] = 1;
    }

    for(int i = 0 ; i < n ; i++){
        if(nodeArr[i]->visited == '0'){
            findSeq(&s,nodeArr,nodeArr[i],arr,n);
        }
    }
    resetNode(nodeArr,n);

    arrScc *result = createArrScc();
    arrScc *temp = NULL;
    arrScc *check = NULL;
    
    while(s!=NULL){
        if(s->node->visited == '0'){
            check = createArrScc();
            findSCC(&s,nodeArr,s->node,tArr,n,&check);
            if(check->size > result->size){
                temp = result;
                result = check;
                deleteArrScc(temp);
                temp = NULL;
            }
        }
        pop(&s);
    }
    insertionSort(result->arr,result->size);

    //free
    deleteArrScc(result);
    for(int i = 0 ; i<n ; i++){
        free(nodeArr[i]);
        free(arr[i]);
        free(tArr[i]);
    }
    free(nodeArr);
    free(tArr);
    free(arr);

    return 0;
}