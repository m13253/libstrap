
#include <assert.h>
#include <stdlib.h>
#include <libstrap.h>

__ls_thread struct memory_functions {
    bool set;
    void *(*malloc_func)(size_t size);
    void *(*calloc_func)(size_t nmemb, size_t size);
    void *(*realloc_func)(void *ptr, size_t size);
    void (*free_func)(void *ptr);
} memory_functions = {false, malloc, calloc, realloc, free};

int ls_memfunc_register(
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
            assert(res != NULL);
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
            assert(res != NULL);
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

void *ls_malloc0_fail(size_t size) {
    if(size != 0) {
        return memory_functions.calloc_func(1, size);
    } else  {
        return NULL;
    }
}

void *ls_calloc(size_t nmemb, size_t size) {
    if(nmemb != 0 && size != 0) {
        void *res = ls_calloc_fail(nmemb, size);
        if(res) {
            return res;
        } else {
            assert(res != NULL);
            abort();
        }
    } else {
        return NULL;
    }
}

void *ls_calloc_fail(size_t nmemb, size_t size) {
    if(nmemb != 0 && size != 0) {
        return memory_functions.calloc_func(nmemb, size);
    } else {
        return NULL;
    }
}

void *ls_realloc(void *ptr, size_t newsize) {
    if(newsize != 0) {
        void *res = ls_realloc_fail(ptr, newsize);
        if(res) {
            return res;
        } else {
            assert(res != NULL);
            abort();
        }
    } else {
        ls_free(ptr);
        return NULL;
    }
}

void *ls_realloc_fail(void *ptr, size_t newsize) {
    if(newsize != 0) {
        if(ptr) {
            return memory_functions.realloc_func(ptr, newsize);
        } else {
            return memory_functions.malloc_func(newsize);
        }
    } else {
        ls_free(ptr);
        return NULL;
    }
}

void *ls_free(void *ptr) {
    if(ptr) {
        memory_functions.free_func(ptr);
    }
    return NULL;
}
