#include <stdio.h>
#include <stdlib.h>

int     main(void)
{
    int a;
    //dprintf(2, "%lu\n", ((size_t)18446744073709551615 + 15));
    dprintf(2, "%p\n", (void*)42);
    //free(&a);
    return 0;
}
