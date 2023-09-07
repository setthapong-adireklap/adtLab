#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    float data;
    struct node *next;
} stack_t;

stack_t *push(stack_t *s, int value){
    
    stack_t *node = (stack_t*)malloc(sizeof(stack_t));
    node->data = value;
    node->next = s;

    return node;
}

float postfixrResult(int size){
    int c;
    float res;
    stack_t *postfix = NULL, *temp=NULL;
    for(int i=0 ; i<size ; i++){
        c = getchar();
        if(c == '+' || c == '-' || c == '*' || c == '/'){
            temp = postfix;
            postfix = temp->next;
            switch(c){
            case '+':
                postfix->data += temp->data;
                free(temp);
                break;
            case '-':
                postfix->data -= temp->data;
                free(temp);
                break;
            case '*':
                postfix->data *= temp->data;
                free(temp);
                break;
            case '/':
                postfix->data /= temp->data;
                free(temp);
                break;
            }
        }
        else{
            postfix = push(postfix, c-48);
        }
    }
    res = postfix->data;
    free(postfix);
    return res;
}

int main(){

    int size;
    scanf("%d\n", &size);
    
    float res = postfixrResult(size);
    printf("%.2f\n", res);

    return 0;
}