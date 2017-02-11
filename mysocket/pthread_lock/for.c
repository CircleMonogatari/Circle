#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, const char* argv[])
{
    char *s="\ta\018bc";
    for(;*s!='\0';s++)
        puts("*");
    return 0;
}
