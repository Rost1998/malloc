#include "private/malloc_private.h"

_Bool    malloc_debug_mode(void)
{
    char *env_var = getenv("FT_MALLOC_DEBUG");
    if (env_var == NULL)
        return 0;
    return *env_var == '1' ? 1 : 0;
}

t_malloc_block *find_block(t_malloc_block *block, void *ptr)
{
    while (block)
    {
        if ((void*)block + sizeof(t_malloc_block) == ptr)
        {
            return block;
        }
        block = block->next;
    }
    return NULL;
}

t_malloc_block *find_block_in_zones(t_malloc_zone *zone, void *ptr)
{
    if (zone == NULL)
        return NULL;
    while (zone)
    {
        t_malloc_block *tmp_block;
        if ((tmp_block = find_block(zone->allocated_blocks, ptr)))
            return tmp_block;
        zone = zone->next;
    }
    return NULL;
}

size_t  malloc_align(size_t size)
{
    size_t ret_size;
    size_t pagesize;

    ret_size = 0;
    pagesize = getpagesize();
    /*
     * Check for overflow
     */
    if (size + (pagesize - (size % pagesize)) > size)
        ret_size = size + (pagesize - (size % pagesize));
    return ret_size;
}

_Bool   is_mul_overflow(uintmax_t a, uintmax_t b)
{
    uintmax_t res;

    if (a == 0 || b == 0)
        return 0;
    res = a * b;
    if (a == res / b)
        return 0;
    else
        return 1;
}

