#include "private/malloc_private.h"

void		free_impl(void *ptr)
{
	_Bool			res;

	if (ptr == NULL)
		return;
	res = free_block(&g_malloc_zones.tiny, ptr);
	if (res == 0)
		res = free_block(&g_malloc_zones.small, ptr);
	if (res == 0)
		free_large(ptr);
}

void		free(void *ptr)
{
	MALLOC_LOG("______TESTTSTART++_________");
	pthread_mutex_lock(&g_mtx_malloc);
	free_impl(ptr);
	pthread_mutex_unlock(&g_mtx_malloc);
	MALLOC_LOG("______TESTTEND++_________");
}

static void	afree_large(t_malloc_block *large)
{
	void	*to_free;

	while (large)
	{   
		to_free = (void*)large + sizeof(t_malloc_block);
		large = large->next;
		free_impl(to_free);
	}   
}

static void	afree_zone(t_malloc_zone *zone)
{
	t_malloc_block	*tmp_block;
	void		*to_free;

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

void		afree(void)
{
	pthread_mutex_lock(&g_mtx_malloc);
	afree_zone(g_malloc_zones.tiny);
	afree_zone(g_malloc_zones.small);
	afree_large(g_malloc_zones.large);
	pthread_mutex_unlock(&g_mtx_malloc);
}

