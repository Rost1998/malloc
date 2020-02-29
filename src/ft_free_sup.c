#include "private/malloc_private.h"

void		free_zone(t_malloc_zone **zone_list, t_malloc_zone *zone)
{
	size_t	zone_size = 0;

	if (zone == NULL)
		return;
	if (zone->prev)
		zone->prev->next = zone->next;
	if (zone->next)
		zone->next->prev = zone->prev;
	if ((*zone_list) == zone)
		(*zone_list) = (*zone_list)->next;
	if (*zone_list == g_malloc_zones.tiny)
		zone_size = sizeof(t_malloc_zone) + (TINY_BLOCK_SIZE + sizeof(t_malloc_block)) * ALLOCATIONS_NUM;
	else if (*zone_list == g_malloc_zones.small)
		zone_size = sizeof(t_malloc_zone) + (SMALL_BLOCK_SIZE + sizeof(t_malloc_block)) * ALLOCATIONS_NUM;
	if (malloc_debug_mode())
		MALLOC_LOG("freeing a memory zone");
	munmap(zone, zone_size);
}

static void	free_block_in(t_malloc_zone *zone_tmp, t_malloc_block *block_tmp)
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
		MALLOC_LOG("freeing a memory block");
}

_Bool		free_block(t_malloc_zone **zone_main, void *ptr)
{
	t_malloc_zone	*zone_tmp;
	t_malloc_block	*block_tmp;

	zone_tmp = *zone_main;
	while (zone_tmp)
	{   
		if ((block_tmp = find_block(zone_tmp->allocated_blocks, ptr)) != NULL)
		{
			free_block_in(zone_tmp, block_tmp);
			if (zone_tmp->allocated_blocks == NULL)
				free_zone(zone_main, zone_tmp);
			return 1;
		}
		zone_tmp = zone_tmp->next;
	}
	return 0;
}

_Bool		free_large(void *ptr)
{
	t_malloc_block	*block_tmp;

	block_tmp = find_block(g_malloc_zones.large, ptr);
	if (block_tmp == NULL)
		return 0;
	if (g_malloc_zones.large == block_tmp)
		g_malloc_zones.large = block_tmp->next;
	if (block_tmp->prev)
		block_tmp->prev->next = block_tmp->next;
	if (block_tmp->next)
		block_tmp->next->prev = block_tmp->prev;
	if (malloc_debug_mode())
		MALLOC_LOG("freeing a large memory block");
	munmap(block_tmp, block_tmp->size);
	return 1;
}

