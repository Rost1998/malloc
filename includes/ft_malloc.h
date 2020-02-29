#ifndef __FT_MALLOC_H__
# define __FT_MALLOC_H__

# include <sys/types.h>
# include <sys/mman.h>

void    *malloc(size_t sz);
void    *realloc(void *ptr, size_t sz);
void    free(void *ptr);
void    afree(void);
void    show_alloc_mem();

void    *reallocf(void *ptr, size_t sz);
void    *reallocarray(void *ptr, size_t nmemb, size_t size);

#endif
