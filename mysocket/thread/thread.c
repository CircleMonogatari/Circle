#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <pthread.h>

//五把锁,或看成无根筷子
pthread_mutex_t mutex[5];


void *dine(void*arg )
{
    int num=*((int*)arg);
    //给五个不同的哲学家分配左右手筷子
    //i因为是从外边进程传进来的,所以
    //可以用来确认哲学家身份
    int left,right;
    if(num<4)
    {
        left=num+1;
        right=num;
    }else if(num==4)
    {
        left=num;
        right=0;
    }

    //分配完成,开始抢筷子,又或者说是开始抢占给自己加锁
    while(1)
    {
        pthread_mutex_lock(&mutex[right]);
            //成功给右手上锁以后,试着给左手上锁,
        if(pthread_mutex_trylock(&mutex[left])==0)
            {
                printf("闲的蛋疼的大兄弟:%c在吃饭\n",'A'+num);
                usleep(100);
                //吃完饭,给自己解锁
                pthread_mutex_unlock(&mutex[left]);
            }
    
        //不管成没成功,都给右手解锁
        pthread_mutex_unlock(&mutex[right]);
        usleep(rand()%300);
    }



}


int main(int argc, const char* argv[])
{
    //在创建子线程之前要先初始化五把锁
    for(int i=0;i<5;i++)
    {
        pthread_mutex_init(&mutex[i],NULL);
    }
    //创建五个子线程用来模拟抢筷子(给自己的函数过程上锁)
      pthread_t thid[5];  //1.创建五个线程 
      pthread_attr_t attr;//2.创建线程得属性 对象
        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);

    //开始创建线程
    for(int i=0;i<5;i++)
    {
        pthread_create(&thid[i],&attr,dine, (void*)&i);
    }

    while(1);

    return 0;
}
