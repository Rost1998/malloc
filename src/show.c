#include "private/malloc_private.h"

static size_t    show_blocks_info(t_malloc_block *block)
{
    size_t size_sum;

    size_sum = 0;
    while (block)
    {
        void *mem = (void*)block + sizeof(t_malloc_block);
        print_block_info(mem, mem + block->size, block->size);
        size_sum += block->size;
        block = block->next;
    }
    return size_sum;
}

static size_t    show_zones_info(t_malloc_zone *zone, t_zone zone_type)
{
    char *prefix;
    size_t size_sum;

    size_sum = 0;
    if (zone_type == TINY_ZONE)
        prefix = "TINY";
    else if (zone_type == SMALL_ZONE)
        prefix = "SMALL";
    while (zone)
    {   
        print_zone_info(prefix, zone);
        size_sum += show_blocks_info(zone->allocated_blocks);
        zone = zone->next;
    }   
    return size_sum;
}

void    show_alloc_mem(void)
{
    size_t allocated_mem_size;

    pthread_mutex_lock(&g_mtx_malloc);
    allocated_mem_size = 0;
    allocated_mem_size += show_zones_info(g_malloc_zones.tiny, TINY_ZONE);
    allocated_mem_size += show_zones_info(g_malloc_zones.small, SMALL_ZONE);
    if (g_malloc_zones.large)
    {   
        print_zone_info("LARGE", g_malloc_zones.large);
        allocated_mem_size += show_blocks_info(g_malloc_zones.large);
    }   
    print_total_mem(allocated_mem_size);
    pthread_mutex_unlock(&g_mtx_malloc);
}

