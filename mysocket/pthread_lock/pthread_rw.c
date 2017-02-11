#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <pthread.h>

int num=0;

void *write_func(void * arg)
{
    while(1){
    num++;
    printf("add---NUM:%d\n",num);
 //   usleep(500);
    }
    return NULL;
}

void *read_func(void *arg)
{
    while(1){
    printf("read  num:%d\n",num);
    }
    return NULL;
}

int main(int argc, const char* argv[])
{
  pthread_t thid[8];

  //创建线程
  for(int i=0;i<3;++i)
  {
      pthread_create(&thid[i],NULL,write_func,NULL);
      }
  for(int i=3;i<8;++i)
  {
      pthread_create(&thid[i],NULL,read_func,NULL);
  }


  //回抽
  for(int i=0;i<8;++i)
  {
      pthread_join(thid[i],NULL);
  }
    
  return 0;
}
