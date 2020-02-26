#include <stdio.h>
//#include <unistd.h>
#include "ft_malloc.h"
#include <dlfcn.h>

#define NUM 5

void    test(void *(*func)(size_t))
{
    void *ptr = func(324);
}

int     main(void)
{
    char *array[NUM];

    int i;
//    void *handle = dlopen("/home/rost/Education/malloc/libft_malloc.so", RTLD_LAZY);

//    void *(*ft_malloc)(size_t);
//    void *(*ft_realloc)(void*, size_t);
//    void *(*ft_free)(void*);
//    void (*show_alloc_mem)(void);

//    ft_malloc = dlsym(handle, "malloc");
//    ft_realloc = dlsym(handle, "realloc");
//    ft_free = dlsym(handle, "free");
//    show_alloc_mem = dlsym(handle, "show_alloc_mem");

    for (i = 0; i < NUM; ++i)
    {
        array[i] = malloc(2048);
        array[i][0] = '0';
    }
    dprintf(2, "malloc done\n");
    show_alloc_mem();
    for (i = 0; i < NUM; ++i)
    {
        array[i] = realloc(array[i], 512);
    }
    dprintf(2, "realloc 1 done\n");
    show_alloc_mem();
    for (i = 0; i < NUM; ++i)
    {
        array[i] = realloc(array[i], 1024 * 1024 * 5);
    }
    dprintf(2, "realloc 2 done\n");
    show_alloc_mem();
    for (i = 0; i < NUM; ++i)
    {
        free(array[i]);
    }
    dprintf(2, "free done\n");
    show_alloc_mem();

    dprintf(2, "----------------------------------------\n");
    void *ptr_m = malloc(4);
    show_alloc_mem();
    free(ptr_m);
    show_alloc_mem();
    dprintf(2, "----------------------------------------\n");
    dprintf(2, "----------------------------------------\n");

    size_t size = 10;
    for (i = 0; i < NUM; ++i)
    {
        array[i] = malloc(size);
        size *= 1.5;
    }
    dprintf(2, "malloc 2 done\n");
    show_alloc_mem();

    afree();
    dprintf(2, "free 2 done\n");
    show_alloc_mem();

    dprintf(2, "----------------------------------------\n");
    dprintf(2, "----------------------------------------\n");
//#if 0
    char *valid_addr = malloc(15);
    
    for (int i = 0; i < 15; ++i)
    {
        valid_addr[i] = 42;
    }
    
    void *ret;

    show_alloc_mem();
    ret = malloc(0);
    dprintf(2, "malloc(0) == %p\n", ret);
    show_alloc_mem();

    //ret = malloc((size_t)-1);
    //dprintf(2, "malloc(%lu) == %p\n", (size_t)-1, ret);
    //show_alloc_mem();

    ret = malloc(9223372036854775807);
    dprintf(2, "malloc(9223372036854775807) == %p\n", ret);
    show_alloc_mem();

    ret = realloc(valid_addr, 0);
    dprintf(2, "realloc(valid_addr, 0) == %p\n", ret);
    show_alloc_mem();

    ret = realloc(valid_addr, 9223372036854775807);
    dprintf(2, "realloc(valid_addr, 9223372036854775807) == %p\n", ret);
    show_alloc_mem();
    dprintf(2, "----------------------------------------\n");

    valid_addr = realloc(NULL, 15);
    for (int i = 0; i < 15; ++i)
    {
        valid_addr[i] = 42;
    }

    for (int i = 0; i < 15; ++i)
    {
        dprintf(2, "%d ", valid_addr[i]);
    }
    dprintf(2, "\n");
    valid_addr = realloc(valid_addr, 8);
    for (int i = 0; i < 8; ++i)
    {
        dprintf(2, "%d ", valid_addr[i]);
    }
    dprintf(2, "\n");
    valid_addr = realloc(valid_addr, 25);
    for (int i = 0; i < 25; ++i)
    {
        dprintf(2, "%d ", valid_addr[i]);
    }
    dprintf(2, "\n");
    valid_addr = realloc(valid_addr, 250);
    for (int i = 0; i < 250; ++i)
    {
        dprintf(2, "%d ", valid_addr[i]);
    }
    dprintf(2, "\n");

    //write(1, (char*)&ptr, 8);
    //write(1, "\n", 1);
    //printf("%p\n", ptr);
    //dlclose(handle);
//#endif
    return 0;
}

