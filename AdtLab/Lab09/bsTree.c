#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *left;
    struct node *right;
} node_t;
typedef node_t bst_t;

bst_t *create(int data){
    bst_t *t = (bst_t*)malloc(sizeof(bst_t));
    t->data = data;
    t->left = NULL;
    t->right = NULL;
    return t;
}

bst_t *searchPa(bst_t* t, bst_t* parent, int data){
    if(t==NULL){
        return t;
    }
    if(t->data == data){
        return parent;
    }

    bst_t *paPos = NULL;
    if(data < t->data){
        paPos = searchPa(t->left,t,data);
    }
    else{
        paPos = searchPa(t->right,t,data);
    }
    
    if(paPos != NULL){
        return paPos;
    }
}

bst_t *search(bst_t* t, int data){
    if(t==NULL){
        return t;
    }
    bst_t *pos = NULL;
    if(data < t->data){
        pos = search(t->left,data);
    }
    else{
        pos = search(t->right,data);
    }

    return (pos==NULL)? t : pos;
}

int find(bst_t *t, int data){
    if(t!=NULL){
        if(t->data == data){
            return 1;
        }
        if(data < t->data){
            return find(t->left, data);
        }
        else{
            return find(t->right, data);
        }
    }
    return 0;
}

int find_min(bst_t *t){
    if(t!=NULL){
        int res = find_min(t->left);
        if(res == 0){
            return t->data;
        }
        else{
            return res;
        }
    }
    return 0;
}

int find_max(bst_t *t){
    if(t!=NULL){
        int res = find_max(t->right);
        if(res == 0){
            return t->data;
        }
        else{
            return res;
        }
    }
    return 0;
}

bst_t *insert(bst_t* t, int data){
    bst_t *node = create(data); 
    if(t == NULL){
        return node;
    }
    bst_t* pos = search(t,data);
    if(data < pos->data){
        pos->left = node;
    }
    else{
        pos->right = node;
    }
    return t;
}

bst_t *delete(bst_t* t, int data){
    bst_t *posPa = searchPa(t,NULL,data);
    bst_t *pos = NULL;
    if(posPa != NULL){
        pos = (data < posPa->data)? posPa->left: posPa->right;
    }
    else{
        pos = t;
    }

    if(pos->left == NULL && pos->right == NULL){
        if(posPa->left == pos){
            posPa->left = NULL;
        }
        else{
            posPa->right = NULL;
        }
        free(pos);
    }
    else if(pos->left != NULL && pos->right != NULL){
        int temp = find_min(pos->right);
        bst_t *posMin = delete(t,temp);
        pos->data = temp;
    }
    else{
        if(pos->left != NULL){
            if(posPa->left == pos){
                posPa->left = pos->left;
            }
            else{
                posPa->right = pos->left;
            }
        }
        else{
            if(posPa->left == pos){
                posPa->left = pos->right;
            }
            else{
                posPa->right = pos->right;
            }
        }
        free(pos);
    }
    return t;
}

int main(void) {
    bst_t *t = NULL;
    int n, i;
    int command, data;
    scanf("%d", &n);
    for (i=0; i<n; i++) {
        scanf("%d", &command);
        switch (command) {
        case 1:
            scanf("%d", &data);
            t = insert(t, data);
            break;
        case 2:
            scanf("%d", &data);
            t = delete(t, data);
            break;
        case 3:
            scanf("%d", &data);
            printf("%d\n", find(t, data));
            break;
        case 4:
            printf("%d\n", find_min(t));
            break;
        case 5:
            printf("%d\n", find_max(t));
            break;
        }
    }
return 0;
}
