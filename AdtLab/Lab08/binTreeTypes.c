#include <stdio.h>
#include <stdlib.h>
#include "week8.h"

#ifndef __bin_tree__
typedef struct node {
int data;
struct node *left;
struct node *right;
} node_t;
typedef node_t tree_t;
#endif

int size(tree_t *t){
    if(t == NULL){
        return 0;
    }
    return size(t->left) + 1 + size(t->right);
}

int height(tree_t *t){
    if(t == NULL){
        return -1;
    }
    int leftD = height(t->left);
    int rightD = height(t->right);

    if(leftD > rightD){
        return leftD+1;
    }
    else{
        return rightD+1;
    }
}

int maxNb(tree_t *t){
    if(t != NULL){
        if(t->left == NULL && t->right == NULL){
            return t->nb;
        }
        else{
            int nbLeft = maxNb(t->left);
            int nbRight = maxNb(t->right);
            
            return (nbLeft > nbRight) ? nbLeft : nbRight;
        }
    }
    return 0;
}

int is_full(tree_t *t){
    if(t != NULL){
        if(t->left == NULL && t->right == NULL){
            return 1;
        }
        else if(t->left != NULL && t->right != NULL){
            return is_full(t->left) && is_full(t->right);
        }
    }
    return 0;
}
int is_perfect(tree_t *t){ 
    int perfectNode = 1;
    for(int i = 0; i<height(t)+1 ;i++){
        perfectNode *= 2;
    }
    if(size(t) == perfectNode-1){
        return 1;
    }
    return 0;
}

int is_complete(tree_t *t){
    if(t != NULL){
        int maxnb = maxNb(t);
        return size(t) == maxnb ? 1 : 0; 
    }
    return 0;
}
int is_degenerate(tree_t *t){
    if(t != NULL){
        if(t->left != NULL && t->right != NULL){
            return 0;
        }
        else if(t->left == NULL && t->right == NULL){
            return 1;
        }
        else{
            if(t->left != NULL){
                return is_degenerate(t->left);
            }
            else{
                return is_degenerate(t->right);
            }
        }
    }
    return 0;
}

int is_skewed(tree_t *t){
    if(t != NULL){
        if(t->left != NULL && t->right != NULL){
            return 0;
        }
        else if(t->left == NULL && t->right == NULL){
            return 1;
        }
        else if(t->nb == 1){
            if(t->left != NULL){
                return is_skewed(t->left);
            }
            else{
                return is_skewed(t->right);
            }
        }
        else{
            if(t->left != NULL){
                if(t->nb % 2 == 0){
                    return (t->left->nb%2 == 0) && is_skewed(t->left);
                }
                else{
                    return 0;
                }
            }
            else{
                if(t->nb % 2 == 1){
                    return t->right->nb%2 && is_skewed(t->right);
                }
                else{
                    return 0;
                }
            }

        }
    }
    return 0;
}

int main(void) {
    tree_t *t = NULL;
    int n, i;
    int parent, child;
    int branch; // 0 root, 1 left, 2 right
    scanf("%d", &n);
    for (i=0; i<n; i++) {
        scanf("%d %d %d", &parent, &child,&branch);
        t = attach(t, parent, child, branch);
    }
    printf("%d %d %d %d %d\n", is_full(t),is_perfect(t), is_complete(t),is_degenerate(t), is_skewed(t));
return 0;
}