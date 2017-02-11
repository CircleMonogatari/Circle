#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>

void myprinSigset()
{
    sigset_t ss;
   int res = sigpending(&ss);
   if(res==-1)
   {
       perror("sigpending error:");
       exit(1);
   }
   for(int i=1;i<33;i++)
   {
       if(sigismember(&ss,i))
       {
           putchar('1');
       }
           else
           {
               putchar('0');
           }
   }
                printf("\n");
}


int main(int argc, const char* argv[])
{
    sigset_t sigs;
   sigemptyset(&sigs);
   sigaddset(&sigs,SIGINT);
   sigaddset(&sigs,SIGQUIT);
   
   int res = sigprocmask(SIG_BLOCK,&sigs,NULL);
   if(res==-1)     
   {
   
       perror("sigprocmask error:");
        exit(1);
   }
   while(1)
   {
        myprinSigset();
   }


    return 0;
}
