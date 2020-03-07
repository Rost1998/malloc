#include <unistd.h>
#include <stdio.h>

int	main(void)
{
	dprintf(2, "%d\n", getpagesize());
	return 0;
}