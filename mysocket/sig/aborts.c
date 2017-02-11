#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>

int main(int argc, const char* argv[])
{

    int i=0;
    while(1)
    {
    printf("%d\n",i);
    sleep(1);
    i++;
    if(i==4)
    {
        abort();
    }
    }

    return 0;
}
