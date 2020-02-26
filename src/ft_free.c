#include "private/malloc_private.h"

void    free_impl(void *ptr)
{
    t_malloc_block *block_tmp;
    t_zone zone_type;

    if (ptr == NULL)
        return;
    block_tmp = ptr - sizeof(t_malloc_block);
    zone_type = (block_tmp->size > TINY_BLOCK_SIZE) + (block_tmp->size > SMALL_BLOCK_SIZE);
    switch (zone_type)
    {
        case TINY_ZONE:
            free_block(&g_malloc_zones.tiny, ptr);
            break;
        case SMALL_ZONE:
            free_block(&g_malloc_zones.small, ptr);
            break;
        case LARGE_ZONE:
            free_large(ptr);
            break;
    }   
}

void    free(void *ptr)
{
    pthread_mutex_lock(&g_mtx_malloc);
    free_impl(ptr);
    pthread_mutex_unlock(&g_mtx_malloc);
}

static void    afree_large(t_malloc_block *large)
{
    void *to_free;

    while (large)
    {   
        to_free = (void*)large + sizeof(t_malloc_block);
        large = large->next;
        free_impl(to_free);
    }   
}

static void    afree_zone(t_malloc_zone *zone)
{
    t_malloc_block *tmp_block;
    void *to_free;

    while (zone)
    {   
        tmp_block = zone->allocated_blocks;
        while (tmp_block)
        {
            to_free = (void*)tmp_block + sizeof(t_malloc_block);
            tmp_block = tmp_block->next;
            if (tmp_block == NULL)
                zone = zone->next;
            free_impl(to_free);
        }
    }   
}

void    afree(void)
{
    pthread_mutex_lock(&g_mtx_malloc);
    afree_zone(g_malloc_zones.tiny);
    afree_zone(g_malloc_zones.small);
    afree_large(g_malloc_zones.large);
    pthread_mutex_unlock(&g_mtx_malloc);
}

