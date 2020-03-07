#include "private/malloc_private.h"

void	malloc_log(const char *log, size_t size, void *addr, size_t sz)
{
	int	fd;

	fd = open("./malloc_debug_info", O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return;
	write(fd, log, size);
	write(fd, " [addr: ", 8);
	print_addr_malloc(addr, fd);
	write(fd, " | size: ", 9);
	print_int_malloc(sz, fd);
	write(fd, "]\n", 2);
    close(fd);
}
