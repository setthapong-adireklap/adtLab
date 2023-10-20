#include <stdio.h>
#include <stdlib.h>

typedef struct tree {
    int freq;
    char *word;
    struct tree *left;
    struct tree *right;
} tree_t;

typedef struct heap {
    tree_t **data;
    int last_index;
} heap_t;

typedef struct stack {
    char data;
    struct stack *next;
} stack_t;

void *push(stack_t **s, char data){
    stack_t *node = (stack_t*)malloc(sizeof(stack_t));
    node->data = data;
    node->next = *s;
    *s = node;
}

heap_t *init_heap(int size){
    heap_t *node = (heap_t*)malloc(sizeof(heap_t));
    node->data = (tree_t**)malloc(sizeof(tree_t*)*size);
    node->last_index = -1;
    return node;
}

tree_t *createTree(char *word,int freq){
    tree_t *node = (tree_t*)malloc(sizeof(tree_t));
    node->freq = freq;
    node->word = word;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void insert(heap_t *h, tree_t *data){
    h->last_index += 1;
    h->data[h->last_index] = data;
    
    int parent = (h->last_index % 2)? h->last_index/2 : (h->last_index-1)/2;
    int child = h->last_index;
    tree_t *temp = NULL;
    while(h->data[parent]->freq > h->data[child]->freq){
        temp = h->data[parent];
        h->data[parent] = h->data[child];
        h->data[child] = temp;
        child = parent;
        parent = (parent % 2)? parent/2 : (parent-1)/2;
    }
}

tree_t *delete_min(heap_t *h){
    tree_t *t = NULL;
    if(h->last_index != -1){
        t = h->data[0];
        h->data[0] = h->data[h->last_index];
        h->last_index -= 1;
        
        int parent = 0, child = 0;

        if(h->last_index >= 2*parent+2){
            child = (h->data[2*parent+2]->freq < h->data[2*parent+1]->freq)? 2*parent+2: 2*parent+1;
        }
        else if(h->last_index >= 2*parent+1){
            child = 2*parent+1;
        }
        
        tree_t *temp;
        while(h->data[parent]->freq > h->data[child]->freq){
            temp = h->data[parent];
            h->data[parent] = h->data[child];
            h->data[child] = temp;
            parent = child;
            if(h->last_index >= 2*parent+2){
                child = (h->data[2*parent+2]->freq < h->data[2*parent+1]->freq)? 2*parent+2: 2*parent+1;
            }
            else if(h->last_index >= 2*parent+1){
                child = 2*parent+1;
            }
        }
    }
    return t;
}

void encodeProcess(heap_t *h){
    tree_t *t1 = delete_min(h);
    tree_t *t2 = delete_min(h);

    tree_t *addT = createTree(NULL,t1->freq + t2->freq);
    addT->left = t1;
    addT->right = t2;

    insert(h,addT);
}

void sequence(tree_t *t, char **wordList,int *seq){
    if(t!=NULL){
        if(t->word != NULL){
            wordList[*seq] = t->word;
            *seq += 1;
        }
        sequence(t->left, wordList, seq);
        sequence(t->right, wordList, seq);
    }
}

tree_t *printCode(tree_t *t,stack_t **s, char *word, char d){
    if(t!=NULL){
        if(t->word == word){
            if(d == 'l'){
                (*s)->data = '0';
            }
            else{
                (*s)->data = '1';
            }
            (*s)->next = NULL;
            return t;
        }
        tree_t *pos = printCode(t->left, s, word, 'l'); 
        if(pos != NULL){
            if(d == 'l'){
                push(s, '0');
            }
            else if(d == 'r'){
                push(s, '1');
            }
            return pos;
        }
        else if(pos == NULL){
            pos = printCode(t->right, s, word, 'r');
            if(pos != NULL && d != 't'){
                if(d == 'l'){
                    push(s, '0');
                }
                else if(d == 'r'){
                    push(s, '1');
                }
            }
            return pos;
        }
    }
    return t;
}

int main(){

    int size, freq, c;
    char *word;

    scanf("%d\n", &size);
    char **wordList = (char**)malloc(sizeof(char*)*size);
    heap_t *encode = init_heap(size);
    for(int i = 0 ; i<size ;i++){
        int j = 0;
        word = (char*)malloc(sizeof(char)*15);
        if(i != 0) {
            c = getchar();
        }
        while((c = getchar()) != ' '){
            word[j] = (char)c;
            j++;
        }
        word[j] = '\0';
        scanf("%d/n", &freq);
        insert(encode,createTree(word,freq));
    }

    while(encode->last_index != 0){
        encodeProcess(encode);
    }

    int seq = 0;
    sequence(encode->data[0], wordList, &seq);
    for(int i = 0 ; i<size ; i++){
        stack_t *s = (stack_t*)malloc(sizeof(stack_t));
        printf("%s: ", wordList[i]);
        printCode(encode->data[0], &s, wordList[i], 't');

        stack_t *temp = s;
        while(temp!=NULL){
            printf("%c", temp->data);
            temp = temp->next;
            free(s);
            s = temp;
        }
        printf("\n");
    }

    return 0;
}