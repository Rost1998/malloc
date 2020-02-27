#include "private/malloc_private.h"

static t_malloc_block	*find_block_in_all_zones(void *ptr, size_t *block_min_size)
{
	t_malloc_block	*block;

	*block_min_size = 0;

	block = find_block_in_zones(g_malloc_zones.tiny, ptr);
	if (block == NULL)
	{
		block = find_block_in_zones(g_malloc_zones.small, ptr);
		*block_min_size = TINY_BLOCK_SIZE;
	}
	if (block == NULL)
	{
		block = find_block(g_malloc_zones.large, ptr);
		*block_min_size = SMALL_BLOCK_SIZE;
	}
	return (block);
}

void			*realloc_impl(void *ptr, size_t sz)
{
	t_malloc_block	*block;
	size_t		block_min_size;
	void		*new;

	if (ptr == NULL)
		return (malloc_impl(sz));
	if (sz == 0)
	{
		free_impl(ptr);
		return (NULL);
	}
	if ((block = find_block_in_all_zones(ptr, &block_min_size)) == NULL)
		return (NULL);
	if (sz > block_min_size && sz <= block->size)
	{
		block->size = sz;
		return (void*)block + sizeof(t_malloc_block);
	}
	new = malloc_impl(sz);
	if (new == NULL)
		return (NULL);
	ft_memcpy(new, (void*)block + sizeof(t_malloc_block), block->size < sz ? block->size : sz);
	free_impl((void*)block + sizeof(t_malloc_block));
	return (new);
}

void			*realloc(void *ptr, size_t sz)
{
	void	*new;

	pthread_mutex_lock(&g_mtx_malloc);
	new = realloc_impl(ptr, sz);
	pthread_mutex_unlock(&g_mtx_malloc);
	return (new);
}

void			*reallocf(void *ptr, size_t sz)
{
	void	*new;

	pthread_mutex_lock(&g_mtx_malloc);
	new = realloc_impl(ptr, sz);
	if (new == NULL)
		free_impl(ptr);
	pthread_mutex_unlock(&g_mtx_malloc);
	return (new);
}

void			*reallocarray(void *ptr, size_t nmemb, size_t size)
{
	void	*new;

	if (is_mul_overflow(nmemb, size))
		return (NULL);

	pthread_mutex_lock(&g_mtx_malloc);
	new = realloc_impl(ptr, nmemb * size);
	pthread_mutex_unlock(&g_mtx_malloc);

	return (new);
}
