#include "private/malloc_private.h"

static void    ft_revarr_malloc(char *str)
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

