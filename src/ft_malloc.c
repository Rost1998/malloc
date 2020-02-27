#include "ft_malloc.h"
#include "private/malloc_private.h"

// 1. проверить на мак ОС по первым пунктам (page reclaims)
// 2. нормы

t_zones g_malloc_zones = {NULL, NULL, NULL};
pthread_mutex_t g_mtx_malloc = PTHREAD_MUTEX_INITIALIZER;

static void     *get_block(t_malloc_zone **zone_main, size_t block_size, size_t mem_required_size)
{
    t_malloc_zone *zone_tmp = *zone_main;
    void *ptr;

    ptr = NULL;
    while (zone_tmp && !zone_tmp->free_blocks)
        zone_tmp = zone_tmp->next;
    if (!zone_tmp)
        zone_tmp = add_zone(zone_main, block_size);
    ptr = block_alloc(zone_tmp, mem_required_size);
    return ptr;
}

void    *malloc_impl(size_t sz)
{
    t_zone zone_type = (sz > TINY_BLOCK_SIZE) + (sz > SMALL_BLOCK_SIZE);
    void *ptr;

    ptr = NULL;
    if (sz == 0)
        return NULL;
    if (zone_type == TINY_ZONE)
        ptr = get_block(&g_malloc_zones.tiny, TINY_BLOCK_SIZE, sz);
    else if (zone_type == SMALL_ZONE)
        ptr = get_block(&g_malloc_zones.small, SMALL_BLOCK_SIZE, sz);
    else if (zone_type == LARGE_ZONE)
        ptr = alloc_large(sz);
    return ptr;
}

void    *malloc(size_t sz)
{
    void *ptr;

    ptr = NULL;
    pthread_mutex_lock(&g_mtx_malloc);
    ptr = malloc_impl(sz);
    pthread_mutex_unlock(&g_mtx_malloc);
    return ptr;
}

void    *calloc(size_t cnt, size_t sz)
{
    void    *ptr;

    if (is_mul_overflow(cnt, sz))
        return NULL;

    ptr = NULL;
    pthread_mutex_lock(&g_mtx_malloc);
    ptr = malloc_impl(cnt * sz);
    if (ptr)
        ft_bzero(ptr, cnt * sz);
    pthread_mutex_unlock(&g_mtx_malloc);
    return ptr;
}
