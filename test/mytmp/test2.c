#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>

int     main(int argc, char **argv)
{
    int first = 0, rv;
    if (access("./shared_obj", F_OK) == -1)
    {
        first = 1;
        //dprinf(2, "access: %s\n", strerror(errno));
        //exit(1);
    }
    int fd = shm_open("/shared_obj", O_RDWR | O_CREAT, 0666);
    if (fd < 0)
    {
        dprintf(2, "shm_open: %s\n", strerror(errno));
        exit(1);
    }
    if (first)
    {
        rv = ftruncate(fd, 10);
        if (rv != 0)
        {
            dprintf(2, "shm_open: %s\n", strerror(errno));
        }
    }
    void *ptr = mmap(NULL, 10, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (argc == 1)
    {
        unsigned char a = 0;
        while (1)
        {
            dprintf(2, "%d (%c) ", ((char*)ptr)[0], ((char*)ptr)[1]);
            ((char*)ptr)[1] = a++;
            int rt = msync(ptr, 10, MS_SYNC | MS_INVALIDATE);
            dprintf(2, "%d\n", rt);
            usleep(500000);
        }
    }
    else
    {
        while (1)
        {
            write(2, ptr, 10);
            write(2, "\n", 1);
            usleep(500000);
        }
    }
    return 0;
}
