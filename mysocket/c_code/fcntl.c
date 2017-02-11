#include<fcntl.h>
#include<sys/stat.h>

int main(int argc, const char* argv[])
{
    int fd=open("test",O_WRONLY|O_CREAT,0777);

    int fd1 =  fcntl(fd,F_GETFL);//获取文件状态，然后修改
    //修改文件状态标示
    fd1=fd1|O_APPEND;
    fcntl(fd,F_SETFL,fd1);
    
    
    write(fd,"bbbbbb",6);



    close(fd);
    return 0;
}
