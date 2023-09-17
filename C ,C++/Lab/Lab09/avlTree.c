#include <stdio.h>
#include <stdlib.h>
#include "week9.h"

#ifndef __avl_tree__
typedef struct node {
    int data;
    int height;
    struct node *left;
    struct node *right;
} node_t;
typedef node_t avl_t;
#endif

avl_t *create(int data){
    avl_t *t = (avl_t*)malloc(sizeof(avl_t));
    t->data = data;
    t->left = NULL;
    t->right = NULL;
    t->height = 0;
    return t;
}

int height(avl_t *t){
    if(t== NULL){
        return -1;
    }
    return t->height;
}

int is_balance(avl_t *t){

    if(abs(height(t->left) - height(t->right)) > 1){
        return 0;
    }
    return 1;
}

avl_t *rotateT(avl_t* t){

    avl_t *nodeB = NULL;
    avl_t *temp = NULL;
    if(height(t->left) > height(t->right)){
        nodeB = t->left;
        temp = nodeB->right;
        t->left = temp;
        nodeB->right = t;
    }
    else{
        nodeB = t->right;
        temp = nodeB->left;
        t->right = temp;
        nodeB->left = t;
    }
    t->height = (height(t->left) > height(t->right))? height(t->left)+1 : height(t->right)+1;  
    nodeB->height = (height(nodeB->left) > height(nodeB->right))? height(nodeB->left)+1 : height(nodeB->right)+1;  
    return nodeB;
}

avl_t *insert(avl_t* t, int data){

    if(t == NULL){ 
        return create(data);
    }

    if(data < t->data){
        if(t->left == NULL){
            t->left = create(data);
        }
        else{
            avl_t *pos = insert(t->left,data);
            t->left = pos; 
        }

        if(t->left->height == t->height){
                t->height += 1;
        }
    }
    else{
        if(t->right == NULL){
            t->right = create(data);
        }
        else{
            avl_t *pos = insert(t->right,data);
            t->right = pos;
        }

        if(t->right->height == t->height){
                t->height += 1;
        }
    }

    if(!(is_balance(t))){
        if(height(t->left) > height(t->right)){
            if(height(t->left->left) < height(t->left->right)){
                t->left = rotateT(t->left);
            }
        }
        else{
            if(height(t->right->left) > height(t->right->right)){
                t->right = rotateT(t->right);
            }
        }
        return rotateT(t);
    }
    return t;
}

int find_min(avl_t *t){
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

avl_t *delete(avl_t *t, int data){

    int deleteStatus = 0;
    if(t->left != NULL || t->right != NULL){
        if(t->data == data){
            deleteStatus = 1;
        }
        if(t->left != NULL){
            if(t->left->data == data){
                deleteStatus = 1;
            }
        }
        if(t->right != NULL){
            if(t->right->data == data){
                deleteStatus = 1;
            }
        }
    }
    else{
        free(t);
        return NULL;
    }
    if(deleteStatus){
        avl_t *deleteNode = (t->left->data == data)? t->left: t->right;
        if(t->data == data){
            deleteNode = t;
        }
        if(deleteNode->left == NULL && deleteNode->right == NULL){
            if(t->left == deleteNode){
                t->left = NULL;
            }
            else{
                t->right = NULL;
            }
            free(deleteNode);
            
        }
        else if(deleteNode->left != NULL && deleteNode->right != NULL){
            int newVal = find_min(deleteNode->right);
            delete(deleteNode,newVal);
            deleteNode->data = newVal;
        }
        else{
            avl_t *temp = (deleteNode->left != NULL)? deleteNode->left: deleteNode->right;
            if(t->left == deleteNode){
                t->left = temp;
            }
            else{
                t->right = temp;
            }
            free(deleteNode);
        }
    }
    else{
        if(data < t->data){
            t->left = delete(t->left,data);
        }
        else{
            t->right = delete(t->right,data);
        }
    }
    //update and rotate after delete
    t->height = (height(t->left) > height(t->right))? height(t->left)+1 : height(t->right)+1;
    if(!(is_balance(t))){
        if(height(t->left) > height(t->right)){
            if(height(t->left->left) < height(t->left->right)){
                t->left = rotateT(t->left);
            }
        }
        else{
            if(height(t->right->left) > height(t->right->right)){
                t->right = rotateT(t->right);
            }
        }
        return rotateT(t);
    }
    return t;
}

int main(void) {
    avl_t *t = NULL;
    int n, i;
    int command, data;
    scanf("%d", &n);
    for (i=0; i<n; i++) {
        scanf("%d", &command);
        switch (command){
        case 1:
            scanf("%d", &data);
            t = insert(t, data);
            break;
        case 2:
            scanf("%d", &data);
            t = delete(t, data);
            break;
        case 3:
            print_tree(t);
            break;
        }
    }

    return 0;
}