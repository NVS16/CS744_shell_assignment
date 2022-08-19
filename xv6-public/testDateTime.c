#include "types.h"
#include "stat.h"
#include "user.h"

int
main(void)
{


    int id = fork();

    if (id != 0) {
        
        printf(1, "Waiting for child to complete\n");
        
        wait(0);
    }
    else {
        printf(1, "Going to sleep\n");
        int id2 = fork();
        if (id2 != 0) wait(0);
        sleep(100);
        printf(1, "I am awake\n");
        int x = getprocesstimedetails(1);
        if (x == -1) printf(1, "WRONGGGG!!");
        exit(0);
    }

    printf(1, "Child has finished\n");
    exit(0);
}
