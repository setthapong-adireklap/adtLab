#include <stdio.h>
#include <stdlib.h>

typedef struct heap {
    int *data;
    int last_index;
} heap_t;

heap_t *init_heap(int m){
    heap_t *node = (heap_t*)malloc(sizeof(heap_t));
    node->data = (int*)malloc(sizeof(int)*m);
    node->last_index = -1;
    return node;
}

int find_max(heap_t* h){
    if(h->last_index != -1){
        return h->data[0];
    }
    return -1;
}

void insert(heap_t *h, int data){
    h->last_index += 1;
    h->data[h->last_index] = data;
    
    int parent = (h->last_index % 2)? h->last_index/2 : (h->last_index-1)/2;
    int child = h->last_index;
    int temp;
    while(h->data[parent] < h->data[child]){
        temp = h->data[parent];
        h->data[parent] = h->data[child];
        h->data[child] = temp;
        child = parent;
        parent = (parent % 2)? parent/2 : (parent-1)/2;
    }
}

void delete_max(heap_t *h){
    if(h->last_index != -1){
        h->data[0] = h->data[h->last_index];
        h->last_index -= 1;
        
        int parent = 0, child = 0;

        if(h->last_index >= 2*parent+2){
            child = (h->data[2*parent+2] > h->data[2*parent+1])? 2*parent+2: 2*parent+1;
        }
        else if(h->last_index >= 2*parent+1){
            child = 2*parent+1;
        }
        
        int temp;
        while(h->data[parent] < h->data[child]){
            temp = h->data[parent];
            h->data[parent] = h->data[child];
            h->data[child] = temp;
            parent = child;
            if(h->last_index >= 2*parent+2){
                child = (h->data[2*parent+2] > h->data[2*parent+1])? 2*parent+2: 2*parent+1;
            }
            else if(h->last_index >= 2*parent+1){
                child = 2*parent+1;
            }
        }
    }
}

void update_key(heap_t *h, int old_key, int new_key){
    int updateAt = -1;
    for(int i = 0 ; i<=h->last_index ; i++){
        if(h->data[i] == old_key){
            h->data[i] = new_key;
                updateAt = i;
            break;
        }
    }
    
    int check = updateAt;
    if(h->last_index >= 2*updateAt+2){
        check = (h->data[2*updateAt+2] > h->data[2*updateAt+1])? 2*updateAt+2: 2*updateAt+1;
    }
    else if(h->last_index >= 2*updateAt+1){
        check = 2*updateAt+1;
    }

    int temp;
    if(h->data[updateAt] < h->data[check]){
        while(h->data[updateAt] < h->data[check]){
            temp = h->data[updateAt];
            h->data[updateAt] = h->data[check];
            h->data[check] = temp;

            updateAt = check;
            if(h->last_index >= 2*updateAt+2){
                check = (h->data[2*updateAt+2] > h->data[2*updateAt+1])? 2*updateAt+2: 2*updateAt+1;
            }
            else if(h->last_index >= 2*updateAt+1){
                check = 2*updateAt+1;
            }
        }
    }
    else{
        int check = (updateAt % 2)? updateAt/2 : (updateAt-1)/2;
        while(h->data[check] < h->data[updateAt]){
            temp = h->data[check];
            h->data[check] = h->data[updateAt];
            h->data[updateAt] = temp;
            updateAt = check;
            check = (check % 2)? check/2 : (check-1)/2;
        }
    }
}

void bfs(heap_t *h){
    for(int i=0 ; i<=h->last_index ; i++){
        printf("%d ", h->data[i]);
    }
    printf("\n");
}

int main(void) {
    heap_t *max_heap = NULL;
    int m, n, i;
    int command, data;
    int old_key, new_key;
    scanf("%d %d", &m, &n);
    max_heap = init_heap(m);
    for (i=0; i<n; i++) {
        scanf("%d", &command);
        switch (command) {
            case 1:
                scanf("%d", &data);
                insert(max_heap, data);
                break;
            case 2:
                delete_max(max_heap);
                break;
            case 3:
                printf("%d\n", find_max(max_heap));
                break;
            case 4:
                scanf("%d %d", &old_key, &new_key);
                update_key(max_heap, old_key,new_key);
                break;
            case 5:
                bfs(max_heap);
                break;
        }
    }

    return 0;
}