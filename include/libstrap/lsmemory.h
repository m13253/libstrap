#ifndef _LS_MEMORY_H
#define _LS_MEMORY_H

extern int ls_memfunc_register(
    void *(*malloc_func)(size_t size),
    void *(*calloc_func)(size_t nmemb, size_t size),
    void *(*realloc_func)(void *ptr, size_t size),
    void (*free_func)(void *ptr)
);
extern void *ls_malloc(size_t size);
extern void *ls_malloc0(size_t size);
extern void *ls_malloc_fail(size_t size);
extern void *ls_malloc0_fail(size_t size);
extern void *ls_calloc(size_t nmemb, size_t size);
extern void *ls_calloc_fail(size_t nmemb, size_t size);
extern void *ls_realloc(void *ptr, size_t newsize);
extern void *ls_realloc_fail(void *ptr, size_t newsize);
extern void *ls_free(void *ptr);

#endif
