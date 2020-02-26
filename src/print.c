#include "private/malloc_private.h"

static void    print_addr_malloc(void *ptr)
{
    char addr[1024];

    ft_memset(addr, 0, 1024);
    write(1, "0x", 2);
    ft_itoa_base_malloc(addr, (uintmax_t)ptr, 16);
    write(1, addr, ft_strlen(addr));
}

static void    print_int_malloc(uintmax_t val)
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
