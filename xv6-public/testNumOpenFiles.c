#include "types.h"
#include "stat.h"
#include "user.h"

int
main(void)
{
    printf(1, "Current process has %d files open.", numOpenFiles(1));
    exit(0);
}
