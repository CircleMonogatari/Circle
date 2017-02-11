#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#define N 1024

void send_headers(char *type)
{
    printf("http/1.1 200 ok\r\n");
    printf("Content-Type:%s\r\n",type);
    printf("Connection:close\r\n");
    printf("\r\n");
}

void send_err(char *title,char*content)
{
    send_headers("404 not found");
    printf("<html>\n");
    printf("<head><title>%s %s</title></head>\n",title,content);
    printf("<body bgcolor=\"#cc99cc\">\n");
    printf("<h4>404 Not Found</h4>h4>\n");
    //    File not found.
    //    <hr>
     //   <address>
      //  <a href="http://www.itcast.cn/">sina</a>a>
      //  </address>address>
      //  </html>

}

int main(int argc, const char* argv[]) // ./xinetd0   /home目录
{
    //1判断参数
    if(argc!=2)
       send_err("argc",NULL);
    //2切换工作目录
    if(chdir(argv[1])==-1)
       send_err("chdir",NULL);
    //3获取http协议头,如果错误send_err
    char line[N]={0};
    char tmp[N]={0};

    if(fgets(line,N,stdin)==NULL)  //line==GET /hello.c http/1.1
       send_err("fgets",NULL);
    //读完stdin的内容
    while(fgets(line,N,stdin)!=NULL)
        {
 //           puts("1");
            if(strcmp(tmp,"\r\n")==0)
                break;
        }
    //字符串拆分
    //    puts("ch sscanf");
    char method[N]={0};//方法
    char path[N]={0};//求情路径文件
    char protocol[N]={0};//协议
    if(sscanf(line,"%[^ ] %[^ ] %[^ ]",method,path,protocol)!=3)
        send_err("sscanf",NULL);
    //判断一个方法
    if(strcmp(method,"GET")!=0)
        send_err("GET",NULL);
    //判断第二个数据是不是/
    if(path[0]!='/')
        send_err("path",NULL);
    char *file=path+1;   //hello.c=>hello.c

    //4判断是否有被请求文件 stat 
    //stat(1path,2addr)
    struct stat path_addr;
    if(stat(file,&path_addr)!=0)    //验证文件是否存在
        send_err("stat",NULL);
    //fopen打开文件
    FILE *fp=NULL;
        fp=fopen(file,"r");
        if(fp==NULL)
            {
                send_err("fopen",NULL);
            }

    //while循环读取文件内容
    char ch;
    //写应答协议
    send_headers("ch");
    while((ch=fgetc(fp))!=EOF)
    {
        putchar(ch);
    }
    //回写数据给浏览器 fputc
    
    //fclose();
    fflush(stdout);
    fclose(fp);
    return 0;
}
