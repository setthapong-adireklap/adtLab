#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TEXTSIZE 21

typedef struct item {
    char *text;
    struct item *next;
} item_t;

typedef struct hash {
    item_t **table;
    int size;
    int hash_key;
} hash_t;

hash_t *init_hashtable(int m, int hash_key){
    hash_t *hashtable = (hash_t*)malloc(sizeof(hash_t));
    hashtable->hash_key = hash_key;
    hashtable->size = m;
    hashtable->table = calloc(m, sizeof(item_t*));
    return hashtable;
}

item_t *createItem(char *text){
    item_t *node = (item_t*)malloc(sizeof(item_t));
    node->text = (char*)malloc(sizeof(char)*strlen(text));
    strcpy(node->text,text);
    node->next = NULL;
    return node;
}

unsigned int preHash(char *text, int hash_key){
    unsigned int hashV = 0;
    for(int i = 0 ; i<strlen(text) ; i++){
        hashV = hashV*hash_key + text[i];
    }
    return hashV;
}

unsigned int hashMap(unsigned int hashV, int size){
    return hashV % size;
}

void insert(hash_t *hashtable, char *text){
    unsigned int hashMapping = hashMap(preHash(text,hashtable->hash_key),hashtable->size);
    item_t *data = createItem(text);
    
    if(hashtable->table[hashMapping] != NULL){
        data->next = hashtable->table[hashMapping];
    }
    hashtable->table[hashMapping] = data;
}

int search(hash_t *hashtable, char *text){
    unsigned int hashMapping = hashMap(preHash(text,hashtable->hash_key),hashtable->size);
    if(hashtable->table[hashMapping] != NULL){
        item_t *temp = hashtable->table[hashMapping];
        while(temp!=NULL){
            if(!strcmp(temp->text,text)){
                return hashMapping;
            }
            temp = temp->next;
        }
    }
    return -1;
}

int main(void){
    hash_t *hashtable = NULL;
    char *text = NULL;
    int m, n, i, hash_key;
    int command;

    scanf("%d %d %d", &m, &n, &hash_key);
    hashtable = init_hashtable(m, hash_key);
    text = (char *)malloc(sizeof(char)*TEXTSIZE);

    for (i=0; i<n; i++) {
        scanf("%d %s", &command, text);
        switch (command) {
            case 1:
                insert(hashtable, text);
                break;
            case 2:
                printf("%d\n",search(hashtable, text));
                break;
        }
    }
    return 0;
}