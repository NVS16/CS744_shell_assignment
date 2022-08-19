#include "types.h"
#include "stat.h"
#include "user.h"

int
main(void)
{
    if (fork() == 0) {
        printf(1, "I am child\n");
        exit(-1);
        //exit(0);
    }

    int x;

    int cid = wait(&x);

    if (cid == -1) exit(-1);

    printf(1, "Child process with PID %d terminated with a status code of: %d\n", cid, x);

    exit(0);
}
