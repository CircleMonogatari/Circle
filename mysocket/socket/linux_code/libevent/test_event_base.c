#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <event2/event.h>

int main(int argc, const char* argv[])
{   //事件 处理框架
    struct event_base* base=NULL;
    base=event_base_new();
    //打印支持的后端 -io函数
    const char ** meths=event_get_supported_methods();
    for(int i=0;meths[i]!=NULL;++i)
    {
        puts(meths[i]);
    }
    //添加事件
    //
    //事件循环
    event_base_dispatch(base);


    //释放event_base
    event_base_free(base);



    return 0;

}
