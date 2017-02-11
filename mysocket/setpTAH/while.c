#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, const char* argv[])
{
    int i=10;
    while(1)
    {
        puts("5");
        i--;
        sleep(1);
    
    }
    return 0;
}
