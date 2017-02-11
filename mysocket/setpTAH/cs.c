#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, const char* argv[])
{
 int i=0;
 for(i=0;i<2;i++)
 {
     pid_t pid=fork();
     if(pid==0)
     {
         break;
     }
 }

 if(i==0)
 {
     execlp("while.out","while.out",NULL);
 }
 else if(i==1)
 {
     sleep(1);
     puts("000000");
     exit(1);
 }
    return 0;
}
