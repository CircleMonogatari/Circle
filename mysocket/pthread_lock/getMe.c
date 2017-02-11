#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

char *GetMemory(void)
{
    char p[]="hello world";
    return p;
}


int main(int argc, const char* argv[])
{
    char *str=NULL;
    str=GetMemory();
    puts(str);

    return 0;
}
