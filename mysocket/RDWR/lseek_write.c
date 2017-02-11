#include "my_head.h"
int main(int argc, const char* argv[])
{
    int fd = open("file_test",O_WRONLY|O_CREAT,0777);
    //写入文件
    write(fd,"wahahaha\n",sizeof("wahahaha")+1);
    lseek(fd,0,SEEK_SET);
    write(fd,"123",sizeof("123"));
    close(fd);

    return 0;
}
