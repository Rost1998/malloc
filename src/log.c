#include "private/malloc_private.h"

void	malloc_log(const char *log, size_t size)
{
	int	fd;

	fd = open("./malloc_debug_info", O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return;
	write(fd, log, size);
	write(fd, "\n", 1);
}
