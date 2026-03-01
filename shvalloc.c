#include <unistd.h>
#include <stdio.h>

struct meta_block { // here i define my meta needed what is needed? 
    size_t size;
    struct meta_block *next; // point to the next block this block is of type meta_block
    struct meta_block *prev; // same but for prev
    int free; // 0 means memory is taken 1 means memory is free

};

struct meta_block *global_head = NULL;


void *find_free_shvspace(struct meta_block *ptr, size_t size) { 
    struct meta_block *current;
    current = global_head;
    
    while (current->free != 0 && size > current->size && current != NULL) {
        current = current->next;
    }


    return current; 
}

void *shvfree(void *ptr) {
    if(!ptr) {
        return NULL; // no pointer was given
    }
    struct meta_block *current = (struct meta_block *) ptr - 1;
    current->free = 1;
}



void *shvalloc(size_t size) {

    struct meta_block *block; 
    struct meta_block *current = global_head;
    
    size_t total_needed_memory = sizeof(struct meta_block) + size;

    void *ptr = sbrk(total_needed_memory);

    if (ptr == (void*) - 1 ) {
        return NULL; // no memory to be given.
    }
    block = (struct meta_block *)ptr;
    if (global_head == NULL) {
        global_head = ptr;
        global_head->prev = NULL;
        global_head->next = NULL;

    } else {
        while (current->next != NULL) {
            current = current->next;
        } 
        current->next = block;
        block->prev = current;
        block->next = NULL;
    }
    block->size = (total_needed_memory);
    block->free = 0;


    return block + 1;
}


int main(){
    
}