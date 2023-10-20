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

int isMatch(int size){
    
    stack_t *parenthesis = NULL;
    int c;

    int res = 0;
    for(int i=0 ; i<size ; i++){
        c = getchar();
        if((char)c == '(' || (char)c == '{' || (char)c == '['){
            parenthesis = push(parenthesis,(char)c);
        }
        else{
            char temp;
            switch((char)c){
            case ')':
                temp = '(';
                break;
            case '}':
                temp = '{';
                break;
            case ']':
                temp = '[';
                break;
            }
            if(parenthesis != NULL){
                if(temp == parenthesis->data){
                    parenthesis = pop(parenthesis);
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
    }
    if(parenthesis != NULL){
        res = 0;
        stack_t *temp = NULL;
        while(parenthesis!=NULL){
            temp = parenthesis;
            parenthesis = parenthesis->next;
            free(temp);
        }
    }
    return res;
}

int main(){
    
    int size;
    scanf("%d\n", &size);

    int res = isMatch(size);

    printf("%d\n",res);

    return 0;
}