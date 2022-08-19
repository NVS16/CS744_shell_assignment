#include "types.h"
#include "stat.h"
#include "user.h"


int main(int argc, char* argv[])
{

    if (argc != 2) {
        exit(-1);
    }

    int pid = atoi(argv[1]);

    if (pid <= 0) {
        exit(-1);
    }

    // printf(1, "Pid is: %d\n", pid);
    int stx1 = numOpenFiles(pid);
    int stx2 = memAlloc(pid);
    int stx3 = getprocesstimedetails(pid);

    if (stx1 == -1 || stx2 == -1 || stx3 == -1) exit(-1);
    
    exit(0);
}