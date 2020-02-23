#include <stdio.h>
#include <unistd.h>

int     main(void)
{
    dprintf(2, "%d\n", getpagesize());
    return 0;
}
