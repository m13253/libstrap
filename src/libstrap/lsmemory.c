
#include <stdlib.h>
#include <libstrap.h>

struct memory_functions {
    bool set;
    void *(*malloc_func)(size_t size);
    void *(*calloc_func)(size_t nmemb, size_t size);
    void *(*realloc_func)(void *ptr, size_t size);
    void (*free_func)(void *ptr);
} memory_functions = {false, malloc, calloc, realloc, free};

int ls_register(
    void *(*malloc_func)(size_t size),
    void *(*calloc_func)(size_t nmemb, size_t size),
    void *(*realloc_func)(void *ptr, size_t size),
    void (*free_func)(void *ptr)
) {
    if(memory_functions.set)
        return LS_FAILURE;
    if(malloc_func)
        memory_functions.malloc_func = malloc_func;
    if(calloc_func)
        memory_functions.calloc_func = calloc_func;
    if(realloc_func)
        memory_functions.realloc_func = realloc_func;
    if(free_func)
        memory_functions.free_func = free_func;
    return LS_SUCCESS;
}

void *ls_malloc(size_t size) {
    if(size != 0) {
        void *res = ls_malloc_fail(size);
        if(res) {
            return res;
        } else {
            abort();
        }
    } else {
        return NULL;
    }
}

void *ls_malloc0(size_t size) {
    if(size != 0) {
        void *res = ls_malloc0_fail(size);
        if(res) {
            return res;
        } else {
            abort();
        }
    } else {
        return NULL;
    }
}

void *ls_malloc_fail(size_t size) {
    if(size != 0) {
        return memory_functions.malloc_func(size);
    } else {
        return NULL;
    }
}
