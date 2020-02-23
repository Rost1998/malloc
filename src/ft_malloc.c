#include "ft_malloc.h"
#include "private/malloc_private.h"

// 1. проверить на мак ОС по первым пунктам (page reclaims)
// 2. нормы

t_zones malloc_zones = {NULL, NULL, NULL};
/*
 * Bonus 1
 */
pthread_mutex_t g_mtx_malloc = PTHREAD_MUTEX_INITIALIZER;

/*
 * Bonus 5
 */
_Bool    malloc_debug_mode(void)
{
    char *env_var = getenv("FT_MALLOC_DEBUG");
    if (env_var == NULL)
        return 0;
    return *env_var == '1' ? 1 : 0;
}

void    ft_revarr_malloc(char *str)
{
    int     i;
    int     len;
    char    tmp;

    i = 0;
    len = ft_strlen(str) - 1;
    while (i < len)
    {
        tmp = str[i];
        str[i++] = str[len];
        str[len--] = tmp;
    }
}

char        *ft_itoa_base_malloc(char *res, uintmax_t a, unsigned base)
{
    const char    *symbols;
    int     i;  

    symbols = "0123456789abcdef";
    if (!a)
        *res = '0';
    i = 0;
    while (a) 
    {
        res[i++] = symbols[a % base];
        a /= base;
    }
    ft_revarr_malloc(res);
    return (res);
}

void    print_addr_malloc(void *ptr)
{
    char addr[1024];

    ft_memset(addr, 0, 1024);
    write(1, "0x", 2);
    ft_itoa_base_malloc(addr, (uintmax_t)ptr, 16);
    write(1, addr, ft_strlen(addr));
}

void    print_int_malloc(uintmax_t val)
{
    char num[1024];

    ft_memset(num, 0, 1024);
    ft_itoa_base_malloc(num, val, 10);
    write(1, num, ft_strlen(num));
}

void    print_block_info(void *ptr_start, void *ptr_end, size_t size)
{
    print_addr_malloc(ptr_start);
    write(1, " - ", 3);
    print_addr_malloc(ptr_end);
    write(1, " : ", 3);
    print_int_malloc(size);
    write(1, "\n", 1);
}

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

void    print_zone_info(const char *prefix, void *ptr)
{
    write(1, prefix, ft_strlen(prefix));
    write(1, " : ", 3);
    print_addr_malloc(ptr);
    write(1, "\n", 1);
}

void    print_total_mem(size_t mem_sz)
{
    write(1, "Total : ", 8);
    print_int_malloc(mem_sz);
    write(1, " bytes\n", 7);
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
    allocated_mem_size += show_zones_info(malloc_zones.tiny, TINY_ZONE);
    allocated_mem_size += show_zones_info(malloc_zones.small, SMALL_ZONE);
    if (malloc_zones.large)
    {
        print_zone_info("LARGE", malloc_zones.large);
        allocated_mem_size += show_blocks_info(malloc_zones.large);
    }
    print_total_mem(allocated_mem_size);
    pthread_mutex_unlock(&g_mtx_malloc);
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

// test all free...
static void    free_zone(t_malloc_zone **zone_list, t_malloc_zone *zone)
{
    size_t zone_size = 0;

    if (zone == NULL)
        return;
    if (zone->prev)
        zone->prev->next = zone->next;
    if (zone->next)
        zone->next->prev = zone->prev;
    if ((*zone_list) == zone)
        (*zone_list) = (*zone_list)->next;
    if (*zone_list == malloc_zones.tiny)
        zone_size = sizeof(t_malloc_zone) + (TINY_BLOCK_SIZE + sizeof(t_malloc_block)) * ALLOCATIONS_NUM;
    else if (*zone_list == malloc_zones.small)
        zone_size = sizeof(t_malloc_zone) + (SMALL_BLOCK_SIZE + sizeof(t_malloc_block)) * ALLOCATIONS_NUM;
    if (malloc_debug_mode())
    {
        MALLOC_LOG("freeing a memory zone");
    }
    munmap(zone, zone_size);
}

static void    free_block(t_malloc_zone **zone_main, void *ptr)
{
    t_malloc_zone *zone_tmp = *zone_main;
    t_malloc_block *block_tmp;

    while (zone_tmp)
    {
        if ((block_tmp = find_block(zone_tmp->allocated_blocks, ptr)) != NULL)
        {
            if (block_tmp == zone_tmp->allocated_blocks)
            {
                zone_tmp->allocated_blocks = zone_tmp->allocated_blocks->next;
                if (zone_tmp->allocated_blocks)
                    zone_tmp->allocated_blocks->prev = NULL;
            }
            if (block_tmp->prev)
                block_tmp->prev->next = block_tmp->next;
            if (block_tmp->next)
                block_tmp->next->prev = block_tmp->prev;
            block_tmp->prev = NULL;
            block_tmp->next = zone_tmp->free_blocks;
            if (zone_tmp->free_blocks)
                zone_tmp->free_blocks->prev = block_tmp;
            zone_tmp->free_blocks = block_tmp;
            if (malloc_debug_mode())
            {
                MALLOC_LOG("freeing a memory block");
            }
            if (zone_tmp->allocated_blocks == NULL)
                free_zone(zone_main, zone_tmp);
            return;
        }
        zone_tmp = zone_tmp->next;
    }
    // nothing was found
}

static void    free_large(void *ptr)
{
    t_malloc_block *block_tmp = find_block(malloc_zones.large, ptr);

    if (block_tmp == NULL)
        return;
    if (malloc_zones.large == block_tmp)
        malloc_zones.large = block_tmp->next;
    if (block_tmp->prev)
        block_tmp->prev->next = block_tmp->next;
    if (block_tmp->next)
        block_tmp->next->prev = block_tmp->prev;
    if (malloc_debug_mode())
    {
        MALLOC_LOG("freeing a large memory block");
    }
    munmap(block_tmp, block_tmp->size);
}

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
            free_block(&malloc_zones.tiny, ptr);
            break;
        case SMALL_ZONE:
            free_block(&malloc_zones.small, ptr);
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

void    *realloc_impl(void *ptr, size_t sz)
{
    t_malloc_block *block;
    size_t block_min_size;
    void *new;

    if (ptr == NULL)
    {
        return malloc_impl(sz);
    }
    if (sz == 0)
    {
        free_impl(ptr);
        return NULL;
    }
    block = find_block_in_zones(malloc_zones.tiny, ptr);
    block_min_size = 0;
    if (block == NULL)
    {
        block = find_block_in_zones(malloc_zones.small, ptr);
        block_min_size = TINY_BLOCK_SIZE;
    }
    if (block == NULL)
    {
        block = find_block(malloc_zones.large, ptr);
        block_min_size = SMALL_BLOCK_SIZE;
    }
    if (block == NULL)
    {
        return NULL;
    }
    if (sz > block_min_size && sz <= block->size)
    {
        block->size = sz;
        return (void*)block + sizeof(t_malloc_block);
    }
    new = malloc_impl(sz);
    if (new == NULL)
        return NULL;
    ft_memcpy(new, (void*)block + sizeof(t_malloc_block), block->size < sz ? block->size : sz);
    free_impl((void*)block + sizeof(t_malloc_block));
    return new;
}

void    *realloc(void *ptr, size_t sz)
{
    void *new;

    pthread_mutex_lock(&g_mtx_malloc);
    new = realloc_impl(ptr, sz);
    pthread_mutex_unlock(&g_mtx_malloc);
    return new;
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

static t_malloc_zone *add_zone(t_malloc_zone **zone_main, size_t block_size)
{
    size_t zsize;
    void *zone_mem;
    t_malloc_block *free_blocks;

    zsize = malloc_align(sizeof(t_malloc_zone) + (block_size + sizeof(t_malloc_block)) * ALLOCATIONS_NUM);
    if (zsize == 0)
        return NULL;
    zone_mem = mmap(0, zsize, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
    if (zone_mem == MAP_FAILED)
    {
        if (malloc_debug_mode())
        {
            MALLOC_LOG("Couldn't allocate a memory zone");
        }
        return NULL;
    }
    if (malloc_debug_mode())
    {
        MALLOC_LOG("allocated a memory zone");
    }
    free_blocks = zone_mem + sizeof(t_malloc_zone);

    t_malloc_zone *zone_tmp = zone_mem;
    zone_tmp->prev = NULL;
    zone_tmp->next = *zone_main;
    if (*zone_main != NULL)
        zone_tmp->next->prev = zone_tmp;
    *zone_main = zone_tmp;
    zone_tmp->allocated_blocks = NULL;
    zone_tmp->free_blocks = free_blocks;
    free_blocks->prev = NULL;
    while ((void*)free_blocks + (block_size + sizeof(t_malloc_block)) * 2 <= zone_mem + zsize)
    {
        free_blocks->next = (void*)free_blocks + block_size + sizeof(t_malloc_block);
        free_blocks->next->prev = free_blocks;
        free_blocks->next->next = NULL;
        free_blocks = free_blocks->next;
    }
    return zone_tmp;
}

static void     *block_alloc(t_malloc_zone *zone, size_t size)
{
    t_malloc_block *tmp;
    
    if (zone == NULL)
        return NULL;
    tmp = zone->free_blocks;
    zone->free_blocks = zone->free_blocks->next;
    if (zone->free_blocks)
        zone->free_blocks->prev = NULL;
    tmp->next = zone->allocated_blocks;
    if (zone->allocated_blocks)
        zone->allocated_blocks->prev = tmp;
    zone->allocated_blocks = tmp;
    tmp->size = size;
    if (malloc_debug_mode())
    {
        MALLOC_LOG("allocated a memory block");
    }
    return ((void*)tmp + sizeof(t_malloc_block));
}

static void     *get_block(t_malloc_zone **zone_main, size_t block_size, size_t mem_required_size)
{
    t_malloc_zone *zone_tmp = *zone_main;
    void *ptr = NULL;

    while (zone_tmp && !zone_tmp->free_blocks)
        zone_tmp = zone_tmp->next;
    if (!zone_tmp)
    {
        zone_tmp = add_zone(zone_main, block_size);
    }
    ptr = block_alloc(zone_tmp, mem_required_size);
    return ptr;
}

static void     *alloc_large(size_t size)
{
    size_t zsize;
    void *mem_block;
    t_malloc_block *block_tmp;

    if (sizeof(t_malloc_block) + size < size)
        return NULL;
    zsize = malloc_align(sizeof(t_malloc_block) + size);
    if (zsize == 0)
        return NULL;
    mem_block = mmap(0, zsize, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
    if (mem_block == MAP_FAILED)
    {
        if (malloc_debug_mode())
        {
            MALLOC_LOG("Couldn't allocate a large memory zone");
        }
        return NULL;
    }
    block_tmp = mem_block;
    block_tmp->prev = NULL;
    block_tmp->next = malloc_zones.large;
    if (malloc_zones.large)
        block_tmp->next->prev = block_tmp;
    block_tmp->size = size;
    malloc_zones.large = block_tmp;
    if (malloc_debug_mode())
    {
        MALLOC_LOG("allocated a large memory zone");
    }
    return mem_block + sizeof(t_malloc_block);
}

void    *malloc_impl(size_t sz)
{
    t_zone zone_type = (sz > TINY_BLOCK_SIZE) + (sz > SMALL_BLOCK_SIZE);
    void *ptr = NULL;

    if (sz == 0)
        return NULL;
    switch (zone_type)
    {
        case TINY_ZONE:
            ptr = get_block(&malloc_zones.tiny, TINY_BLOCK_SIZE, sz);
            break;
        case SMALL_ZONE:
            ptr = get_block(&malloc_zones.small, SMALL_BLOCK_SIZE, sz);
            break;
        case LARGE_ZONE:
            ptr = alloc_large(sz);
            break;
        default:
            break;
    }
    return ptr;
}

void    *malloc(size_t sz)
{
    void *ptr = NULL;

    pthread_mutex_lock(&g_mtx_malloc);
    ptr = malloc_impl(sz);
    pthread_mutex_unlock(&g_mtx_malloc);
    return ptr;
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

/*
 * Bonus 2
 */
void    *calloc(size_t cnt, size_t sz)
{
    void    *ptr;

    if (is_mul_overflow(cnt, sz))
        return NULL;

    pthread_mutex_lock(&g_mtx_malloc);
    ptr = malloc_impl(cnt * sz);
    if (ptr)
    {
        ft_bzero(ptr, cnt * sz);
    }
    pthread_mutex_unlock(&g_mtx_malloc);
    return ptr;
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

/*
 * Bonus 3
 */
void    afree(void)
{
    pthread_mutex_lock(&g_mtx_malloc);
    afree_zone(malloc_zones.tiny);
    afree_zone(malloc_zones.small);
    afree_large(malloc_zones.large);
    pthread_mutex_unlock(&g_mtx_malloc);
}

/*
 * Bonus 4
 */
void    *reallocf(void *ptr, size_t sz)
{
    void    *new;

    pthread_mutex_lock(&g_mtx_malloc);
    new = realloc_impl(ptr, sz);
    if (new == NULL)
    {
        free_impl(ptr);
    }
    pthread_mutex_unlock(&g_mtx_malloc);
    return (new);
}

/*
 * Bonus 6
 */
void    *reallocarray(void *ptr, size_t nmemb, size_t size)
{
    void *new;

    if (is_mul_overflow(nmemb, size))
        return NULL;

    pthread_mutex_lock(&g_mtx_malloc);
    new = realloc_impl(ptr, nmemb * size);
    pthread_mutex_unlock(&g_mtx_malloc);

    return (new);
}

