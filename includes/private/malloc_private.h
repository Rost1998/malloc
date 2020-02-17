#ifndef MALLOC_PRIVATE_H
# define MALLOC_PRIVATE_H

# define MALLOC_LOG_PREFIX "FT_MALLOC DEBUG: "
# define MALLOC_LOG(str) write(1, MALLOC_LOG_PREFIX str "\n", 17 + ft_strlen(str) + 1)

# define ALLOCATIONS_NUM 100

typedef enum {
    TINY_ZONE,
    SMALL_ZONE,
    LARGE_ZONE
} t_zone;

# define TINY_BLOCK_SIZE (1 << 6)
# define SMALL_BLOCK_SIZE (1 << 10)

# define MALLOC_ZONE_DATA (1 << 7)

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

extern pthread_mutex_t g_mtx_malloc;

void    *malloc_impl(size_t sz);
void    *realloc_impl(void *ptr, size_t sz);
void    free_impl(void *ptr);

#endif
