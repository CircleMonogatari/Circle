#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/time.h>
#include <signal.h>


int num=1;

void myfunc(int sig)
{
    num=0;
}


int main()
{
        //屏蔽时钟的信号,防止时钟时间到了以后关闭
    sigset_t set;
    sigemptyset(&set);
 //   sigaddset(&set,SIGALRM);

    sigprocmask(SIG_BLOCK,&set,NULL);

//信号捕捉
    signal(SIGALRM,myfunc);


        //自定义时钟,5秒后执行,一次
    struct itimerval stm;
    stm.it_value.tv_sec=5;
    stm.it_value.tv_usec=0;
    stm.it_interval.tv_sec=0;
    stm.it_interval.tv_usec=0;
    
    setitimer(ITIMER_REAL,&stm,NULL);
    
    

    while(num){
    puts("大兄弟出来了!");
   sleep(1);
    }

puts("mmmmm");
    return 1;
}
