#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, const char* argv[])
{
    int fp=open("x.c",O_RDWR|O_CREAT|O_EXCL,0777);
    if (fp==-1) 
    { 
        printf("文件存在\n");
    } 
    return 0;
}
