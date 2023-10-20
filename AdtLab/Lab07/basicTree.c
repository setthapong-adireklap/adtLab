#include <stdio.h>
#include <stdlib.h>

typedef struct tree{
    int value;
    int level;
    struct tree *next_sibling;
    struct tree *first_child;
}tree_t;

typedef struct snode {
    int value;
    struct snode *next;
} stack_t;

typedef struct qnode {
    tree_t *tNode;
    struct qnode *next;
} queue_t;

queue_t *enqueue(queue_t **q, tree_t *t){
    queue_t *node = (queue_t*)malloc(sizeof(queue_t));
    node->tNode = t;
    node->next = NULL;
    if(*q == NULL){
        return node;
    }
    else{
        queue_t *temp = *q;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = node;
    }
    return *q;
}

void dequeue(queue_t **q){
    printf("%d ",(*q)->tNode->value);
    queue_t *temp = *q;
    *q = (*q)->next;
    free(temp);
}

queue_t *createQueue(tree_t *t){
    queue_t *q = (queue_t*)malloc(sizeof(queue_t));
    q->tNode = t;
    q->next = NULL;
    return q;
}

stack_t *push(stack_t **s, int v){
    stack_t *node = (stack_t*)malloc(sizeof(stack_t));
    node->value = v;
    node->next = *s;
    return node;
}

tree_t *createTree(int v){
    tree_t *t = (tree_t*)malloc(sizeof(tree_t));
    t->value = v;
    t->level = 0;
    t->next_sibling = NULL;
    t->first_child = NULL;
    return t;
}

tree_t *searchPos(tree_t *t,int v){
    if(t == NULL){
        return t;
    }
    if(t->value == v){
        return t;
    }
    tree_t *pos = searchPos(t->first_child,v);
    if(pos != NULL){
        return pos;
    }
    else{
        return searchPos(t->next_sibling,v);
    }
}

tree_t *searchParent(tree_t *t,tree_t *parentNode,int v){
    if(t == NULL){
        return NULL;
    }
    if(t->value == v){
        return parentNode;
    }
    tree_t *pos = searchParent(t->first_child,t,v);
    if(pos != NULL){
        return pos;
    }
    else{
        return searchParent(t->next_sibling,parentNode,v);
    }
}

int search(tree_t *t, int v){
    if(searchPos(t,v) != NULL){
        return 1;
    }
    return 0;
}

tree_t *findPath(tree_t *t,stack_t **path,int v){
    if(t == NULL){
        return t;
    }
    else if(t->value == v){
        *path = push(path,v);
        return t;
    }
    tree_t *pos = findPath(t->first_child,path,v);
    if(pos != NULL){
        *path = push(path,t->value);
        return pos;
    }
    else{
        return findPath(t->next_sibling,path,v);
    }
}

int depth(tree_t *t, int node){
    int length = 0;
    stack_t *path = NULL;
    tree_t *endPos = findPath(t,&path,node);

    stack_t *temp = NULL;
    while(path!=NULL){
        length++;
        temp = path->next;
        free(path);
        path = temp;
    }
    return length-1;
}

tree_t *attach(tree_t *t,int parent, int child){
    
    tree_t *node = createTree(child);
    if(parent == -1){
        return node;
    }
    tree_t *pos = searchPos(t,parent);
    
    node->level = depth(t,parent) + 1;
    if(pos->first_child == NULL){
        pos->first_child = node;
        
    }
    else{
        pos = pos->first_child;
        while(pos->next_sibling != NULL){
            pos = pos->next_sibling;
        }
        pos->next_sibling = node;
    }

    return t;
}

int degree(tree_t *t, int node){
    int count = 0;
    tree_t *pos = searchPos(t,node)->first_child;
    while(pos!=NULL){
        count++;
        pos = pos->next_sibling;
    }
    return count;
}

int is_root(tree_t *t, int node){
    tree_t *check = searchPos(t,node);
    if(check == NULL){
        return 0;
    }
    else if(check->level == 0){
        return 1;
    }
    return 0;
}

int is_leaf(tree_t *t, int node){
    tree_t *pos = searchPos(t,node); 
    if(pos == NULL){
        return 0;
    }
    else if(pos->first_child == NULL){
        return 1;
    }
    return 0;
}

void siblings(tree_t *t, int node){
    tree_t *pos = searchParent(t,NULL,node);
    if(pos != NULL){
        pos = pos->first_child;
    }
    while(pos != NULL){
        if(pos->value != node){
            printf("%d ", pos->value);
        }    
        pos = pos->next_sibling;
    }
    printf("\n");
}


void print_path(tree_t *t, int start, int end){
    stack_t *path = NULL;
    stack_t *temp = NULL;
    tree_t *endPos = findPath(searchPos(t,start),&path,end);
    while(path!=NULL){
        printf("%d ", path->value);
        temp = path->next;
        free(path);
        path = temp;
    }
    printf("\n");
}

int path_length(tree_t *t, int start, int end){
    int length = 0;
    stack_t *path = NULL;
    tree_t *endPos = findPath(searchPos(t,start),&path,end);

    stack_t *temp = NULL;
    while(path!=NULL){
        length++;
        temp = path->next;
        free(path);
        path = temp;
    }
    return length;
}

void ancestor(tree_t *t, int node){
    stack_t *path = NULL;
    stack_t *temp = NULL;
    tree_t *endPos = findPath(t,&path,node);
    while(path!=NULL){
        printf("%d ", path->value);
        temp = path->next;
        free(path);
        path = temp;
    }
    printf("\n");
}

void destroy(tree_t *t){
    if(t != NULL){
        destroy(t->first_child);
        destroy(t->next_sibling);
        free(t);
    }
}

tree_t *detach(tree_t *t,int node){
    tree_t *dNode = searchPos(t,node);
    tree_t *pdNode = searchParent(t,NULL,node);
    tree_t *temp = NULL;

    if(pdNode != NULL){
        if(pdNode->first_child != NULL && pdNode->first_child->value != node){
            pdNode = pdNode->first_child;
            while(pdNode != dNode){
                temp = pdNode;
                pdNode = pdNode->next_sibling;
            }
            temp->next_sibling = pdNode->next_sibling;
        }
        else{
            pdNode->first_child = dNode->next_sibling;
        }
        dNode->next_sibling = NULL;
        destroy(dNode);
    }
    else{
        destroy(dNode);
        t = NULL;
    }
    return t;
}

void dfs(tree_t *t){
    if(t != NULL){
        printf("%d ",t->value);
        dfs(t->first_child);
        dfs(t->next_sibling);
        if(is_root(t,t->value)){
            printf("\n");
        }
    }
}

void bfs(tree_t *t){
    tree_t *check = t;
    if(check != NULL){
        queue_t *qBfs = createQueue(check);
        while(qBfs != NULL){
            if(check->next_sibling == NULL){
                if(check->first_child != NULL){
                    qBfs = enqueue(&qBfs,check->first_child);
                    tree_t *temp = check->first_child;
                    while(temp != NULL){
                        temp = temp->next_sibling;
                        if(temp != NULL){
                            qBfs = enqueue(&qBfs,temp);
                        }
                    }
                }
                dequeue(&qBfs);
            }
            else{
                if(check->first_child != NULL){
                    qBfs = enqueue(&qBfs,check->first_child);
                    tree_t *temp = check->first_child;
                        while(temp != NULL){
                            temp = temp->next_sibling;
                            if(temp != NULL){
                                qBfs = enqueue(&qBfs,temp);
                            }
                        }
                }
                dequeue(&qBfs);
            }
            if(qBfs != NULL){
                check = qBfs->tNode;
            }
        }
    }
    printf("\n");
}

void descendant(tree_t *t, int node){
    tree_t *pos = searchPos(t,node);
    bfs(pos);
}

void print_tree(tree_t *t){
    if(t != NULL){
        for(int i = 0 ; i< t->level ; i++){
            printf("    ");
        }
        printf("%d\n",t->value);
        print_tree(t->first_child);
        print_tree(t->next_sibling);
    }
}

int main(void) {
    tree_t *t = NULL;
    int n, i, command;
    int parent, child, node, start, end;
    scanf("%d", &n);
    for (i=0; i<n; i++) {
        scanf("%d", &command);
        switch(command) {
            case 1:
                scanf("%d %d", &parent, &child);
                t = attach(t, parent, child);
                break;
            case 2:
                scanf("%d", &node);
                t = detach(t, node);
                break;
            case 3:
                scanf("%d", &node);
                printf("%d\n", search(t, node));
                break;
            case 4:
                scanf("%d", &node);
                printf("%d\n", degree(t, node));
                break;
            case 5:
                scanf("%d", &node);
                printf("%d\n", is_root(t, node));
                break;
            case 6:
                scanf("%d", &node);
                printf("%d\n", is_leaf(t, node));
                break;
            case 7:
                scanf("%d", &node);
                siblings(t, node);
                break;
            case 8:
                scanf("%d", &node);
                printf("%d\n", depth(t, node));
                break;
            case 9:
                scanf("%d %d", &start, &end);
                print_path(t, start, end);
                break;
            case 10:
                scanf("%d %d", &start, &end);
                printf("%d\n",path_length(t, start, end));
                break;
            case 11:
                scanf("%d", &node);
                ancestor(t, node);
                break;
            case 12:
                scanf("%d", &node);
                descendant(t, node);
                break;
            case 13:
                bfs(t);
                break;
            case 14:
                dfs(t);
                break;
            case 15:
                print_tree(t);
                break;
        }
    }
    return 0;
}
