#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char* argv[])
{
    if (argc > 1) {
        exit(-1);
    }
    

    psinfo();
    
    exit(0);
}