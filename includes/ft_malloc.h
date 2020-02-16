#ifndef __FT_MALLOC_H__
# define __FT_MALLOC_H__

# include <sys/mman.h>
# include <pthread.h>
# include "libft.h"

void    *malloc(size_t sz);
void    *realloc(void *ptr, size_t sz);
void    free(void *ptr);
void    afree(void);
void    show_alloc_mem();

#endif
