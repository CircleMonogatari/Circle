#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
int main(int argc, const char* argv[])
{
    int fp= open("test.c",O_WRONLY|O_CREAT,0777);

    int fp1=dup(fp);

       write(fp1,"mmm",3);
       write(fp,"sss",3);

       close(fp);

    return 0;
}
