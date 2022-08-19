#include "types.h"
#include "stat.h"
#include "user.h"

int
main(void)
{
    printf(1, "Initial break point: %d Bytes\n", sbrk(0));
    printf(1, "The amount of heap allocated for the current process: %d Bytes\n", memAlloc(1));
    sbrk(4);
    printf(1, "The amount of heap allocated for the current process: %d Bytes\n", memAlloc(1));
    exit(0);
}
