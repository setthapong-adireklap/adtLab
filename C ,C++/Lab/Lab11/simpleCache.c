#include <stdio.h>
#include <stdlib.h>

typedef struct cell {
    int data;
    int mem_addr;
} cell_t;

typedef struct hash {
    cell_t *table;
    int cache_size;
} hash_t;

typedef hash_t cache_t;
typedef int memory_t;

memory_t *init_memory(int size) {
    memory_t *memory = (memory_t *)malloc(sizeof(memory_t)*size);
    int i = 0;
    // Randomly assign integers to memory
    for (i=0; i<size; i++)
        memory[i] = rand();
    return memory;
}

cell_t createCell_t(int data, int mem_addr){
    cell_t a;
    a.data = data;
    a.mem_addr = mem_addr;
    return a;
}

cache_t *init_cache(int size){
    cache_t *cache = (cache_t*)malloc(sizeof(cache_t));
    cache->cache_size = size;
    cache->table = calloc(size, sizeof(cell_t));
    //init all data value as -1 
    for(int i = 0 ; i<size ; i++){
        cache->table[i] = createCell_t(-1,-1);
    }
    return cache;
}

void get_data(int addr, memory_t *memory, cache_t *cache){
    unsigned int cache_index = addr % cache->cache_size;
    unsigned int data = memory[addr];

    //case 1 
    if(cache->table[cache_index].data == -1){
        printf("Load from memory\nData: %d\n", data);
        cache->table[cache_index].data = data;
        cache->table[cache_index].mem_addr = addr;
    }
    else if(cache->table[cache_index].data != -1){
        //case 3
        if(cache->table[cache_index].data == data){
            printf("Address %d is loaded\nData: %d\n", addr, cache->table[cache_index].data);
        }
        //case 2
        else{
            printf("Index: %d is used\nLoad from memory\nData: %d\n", cache_index, data);
            cache->table[cache_index].data = data;
            cache->table[cache_index].mem_addr = addr;
        }
    }
}

int main(void) {
    memory_t *memory = NULL;
    cache_t *cache = NULL;
    int memory_size, cache_size;
    int i, n, addr;
    scanf("%d %d %d", &memory_size,&cache_size, &n);
    memory = init_memory(memory_size);
    cache = init_cache(cache_size);
    for (i=0; i<n; i++) {
        printf("Load address: ");
        scanf("%d", &addr);
        get_data(addr, memory, cache);
    }
return 0;
}
