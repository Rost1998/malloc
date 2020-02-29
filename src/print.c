#include "private/malloc_private.h"

void		print_addr_malloc(void *ptr, int fd)
{
	char	addr[1024];

	ft_memset(addr, 0, 1024);
	write(fd, "0x", 2);
	ft_itoa_base_malloc(addr, (unsigned long long)ptr, 16);
	write(fd, addr, ft_strlen(addr));
}

void		print_int_malloc(unsigned long long val, int fd)
{
	char	num[1024];

	ft_memset(num, 0, 1024);
	ft_itoa_base_malloc(num, val, 10);
	write(fd, num, ft_strlen(num));
}

void		print_block_info(void *ptr_start, void *ptr_end, size_t size, int fd)
{
	print_addr_malloc(ptr_start, fd);
	write(fd, " - ", 3);
	print_addr_malloc(ptr_end, fd);
	write(fd, " : ", 3);
	print_int_malloc(size, fd);
	write(fd, "\n", 1);
}

void		print_zone_info(const char *prefix, void *ptr, int fd)
{
	write(fd, prefix, ft_strlen(prefix));
	write(fd, " : ", 3);
	print_addr_malloc(ptr, fd);
	write(fd, "\n", 1);
}

void		print_total_mem(size_t mem_sz, int fd)
{
	write(fd, "Total : ", 8);
	print_int_malloc(mem_sz, fd);
	write(fd, " bytes\n", 7);
}
