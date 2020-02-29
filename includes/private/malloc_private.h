#ifndef MALLOC_PRIVATE_H
# define MALLOC_PRIVATE_H

# include <sys/types.h>
# include <sys/mman.h>
# include <pthread.h>
# include "libft.h"

# define MALLOC_LOG_PREFIX "FT_MALLOC DEBUG: "
# define MALLOC_LOG(str) write(1, MALLOC_LOG_PREFIX str "\n", 17 + ft_strlen(str) + 1)

# define ALLOCATIONS_NUM 100

typedef enum {
    TINY_ZONE,
    SMALL_ZONE,
    LARGE_ZONE
} t_zone;

# define FT_KB (1024)
# define FT_MB (1024 * 1024)

# define TINY_BLOCK_SIZE (FT_KB)
# define SMALL_BLOCK_SIZE (FT_MB)

typedef struct s_malloc_block {
    struct s_malloc_block   *next;
    struct s_malloc_block   *prev;
    size_t                  size;
} t_malloc_block;

typedef struct s_malloc_zone {
    struct s_malloc_zone    *next;
    struct s_malloc_zone    *prev;
    t_malloc_block          *allocated_blocks;
    t_malloc_block          *free_blocks;
} t_malloc_zone;

typedef struct s_zones {
    t_malloc_zone   *tiny;
    t_malloc_zone   *small;
    t_malloc_block  *large;
} t_zones;

extern t_zones g_malloc_zones;
extern pthread_mutex_t g_mtx_malloc;

void    *malloc_impl(size_t sz);
void    *realloc_impl(void *ptr, size_t sz);
void    free_impl(void *ptr);

_Bool		malloc_debug_mode(void);
t_malloc_block *find_block(t_malloc_block *block, void *ptr);
t_malloc_block *find_block_in_zones(t_malloc_zone *zone, void *ptr);
size_t		malloc_align(size_t size);
_Bool		is_mul_overflow(uintmax_t a, uintmax_t b);
t_malloc_zone *add_zone(t_malloc_zone **zone_main, size_t block_size);
void		*alloc_large(size_t size);
void		*block_alloc(t_malloc_zone *zone, size_t size);
void		print_block_info(void *ptr_start, void *ptr_end, size_t size);
void		print_zone_info(const char *prefix, void *ptr);
void		print_total_mem(size_t mem_sz);
char        *ft_itoa_base_malloc(char *res, uintmax_t a, unsigned base);
void		free_zone(t_malloc_zone **zone_list, t_malloc_zone *zone);
_Bool		free_block(t_malloc_zone **zone_main, void *ptr);
_Bool		free_large(void *ptr);

#endif
