#include "private/malloc_private.h"

void			*block_alloc(t_malloc_zone *zone, size_t size)
{
	t_malloc_block	*tmp;
	
	if (zone == NULL)
		return (NULL);
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
		MALLOC_LOG("allocated a memory block", tmp, size);
	return ((void*)tmp + sizeof(t_malloc_block));
}

static t_malloc_zone	*alloc_zone(size_t block_size, size_t *zsize)
{
	void	*zone_mem;

	*zsize = malloc_align(sizeof(t_malloc_zone) + (block_size + sizeof(t_malloc_block)) * ALLOCATIONS_NUM);
	if (*zsize == 0)
		return (NULL);
	zone_mem = mmap(0, *zsize, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (zone_mem == MAP_FAILED)
	{
		if (malloc_debug_mode())
			MALLOC_LOG("Couldn't allocate a memory zone", NULL, *zsize);
		return (NULL);
	}
	if (malloc_debug_mode())
		MALLOC_LOG("allocated a memory zone", zone_mem, *zsize);
	return (zone_mem);
}

t_malloc_zone		*add_zone(t_malloc_zone **zone_main, size_t block_size)
{
	size_t		zsize;
	void		*zone_mem;
	t_malloc_block	*free_blocks;
	t_malloc_zone	*zone_tmp;

	if ((zone_mem = alloc_zone(block_size, &zsize)) == NULL)
		return (NULL);
	free_blocks = zone_mem + sizeof(t_malloc_zone);
	zone_tmp = zone_mem;
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
	return (zone_tmp);
}

void			*alloc_large(size_t size)
{
	size_t		zsize;
	void		*mem_block;
	t_malloc_block	*block_tmp;

	if (sizeof(t_malloc_block) + size < size)
		return (NULL);
	if ((zsize = malloc_align(sizeof(t_malloc_block) + size)) == 0)
		return (NULL);
	mem_block = mmap(0, zsize, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (mem_block == MAP_FAILED)
	{
		if (malloc_debug_mode())
			MALLOC_LOG("Couldn't allocate a large memory zone", NULL, zsize);
		return (NULL);
	}
	block_tmp = mem_block;
	block_tmp->prev = NULL;
	block_tmp->next = g_malloc_zones.large;
	if (g_malloc_zones.large)
		block_tmp->next->prev = block_tmp;
	block_tmp->size = size;
	g_malloc_zones.large = block_tmp;
	if (malloc_debug_mode())
		MALLOC_LOG("allocated a large memory zone", mem_block, zsize);
	return (mem_block + sizeof(t_malloc_block));
}
