#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(int argc, const char* argv[])
{
    int fd=open ("test",O_WRONLY|O_CREAT,0777);

    int fd1=666;
    dup2(fd,fd1);

    write(fd1,"qqqq",4);
    close(fd);


    return 0;
}
