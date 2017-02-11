#include <my_head.h>
int main(int argc, const char* argv[])
{
    int fd=open("file_test",O_RDONLY);
    char buf[1024];
    while(read(fd,buf,1024));
    {
        puts(buf);
    }

    close(fd);
    return 0;
}
