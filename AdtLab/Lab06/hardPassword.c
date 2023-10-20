#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    char data;
    struct node *next;
}stack_t;

stack_t *push(stack_t *s, char value){
    
    stack_t *node = (stack_t*)malloc(sizeof(stack_t));
    node->data = value;
    node->next = s;

    return node;
}

stack_t *pop(stack_t *s){
    
    if(s == NULL){
        return s;
    }
    stack_t *temp = s;
    s = s->next;
    free(temp);

    return s;
}

int main(){
    
    int c;
    int state = 0, res = 0, stop = 0;
    stack_t *passWord = NULL;

    while((c = getchar()) != 'y'){
        if(c == 'x'){
            state = 1;
            continue;
        }
        
        if(state == 0){
            passWord = push(passWord, (char)c);
        }
        else if(passWord != NULL){
            if(c == passWord->data){
                passWord = pop(passWord);
                res = 1;
            }
            else{
                res = 0;
                break;
            }
        }
        else{
            res = 0;
            break;
        }
    }

    if(passWord != NULL){
        res = 0;
        stack_t *temp = NULL;
        while(passWord != NULL){
            temp = passWord;
            passWord = passWord->next;
            free(temp);
        }
    }
    printf("%d\n",res);

    return 0;
}