//#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#define N 1024
#define __err send_err(500,"error","我懒所以没写")


void send_headers(char *type, off_t length)//发送协议头文件
{
	printf("%s %d %s\r\n", "HTTP/1.1", 200, "0k");
	printf("Content-Type:%s\r\n", type);
	printf("Content-Length:%ld\r\n", (int64_t)length);
	printf("Connection: close\r\n");
	printf("\r\n");
}

void send_err(int status,char *title,char *text)//发送错
{
	send_headers("text/html", -1);

	printf("<html><head><title>%d %s</title></head>\n", status, title);
	printf("<body bgcolor=\"#cc99cc\"><h4>%d %s</h4>\n", status, title);
	printf("%s\n", text);
	printf("<hr>\n</body>\n</html>\n");
	fflush(stdout);

	/*<html><head><title>错误号 错误名</title></head>
	*<body bgcolor="#cc99cc"><h4>错误号 错误名</h4>
	*错误原因描述
	*<hr>
	*</body>
	*</html>
	*/
	//exit(1);
}

int hexit(char c)
{
    if(c>='0' && c<='9')
    {
        return c-'0';
    }
    if(c>='a' && c<='f')
    {
        return c-'a'+10;
    }
    if(c>='A' && c<='F')
    {
        return c-'A'+10;
    }
}

void strdecode(char *to,char *from)
{
    for(;*from!='\0';++to,++from)
    {
        if(from[0]=='%'&& isxdigit(from[1]) && isxdigit(from[2]))
        {
            *to=hexit(from[1])*16+hexit(from[2]);
            from+=2;
        }
        else
            *to=*from;
    }
    *to= '\0';
}

int main(int argc,char *argv[]) {

	if (argc != 2)
	{
		__err;
	}
	if (argv[1] < 0)
	{
		__err;
	}
	if (chdir(argv[1]) < 0)
	{
		__err;
	}

	char line[N];
	char tmp[N];

	if (fgets(line, N, stdin) == 0)
	{
		send_err(400,"error","get line error");
	}

					#if debug
						puts(line);
					#endif
	

	while (fgets(tmp, N, stdin))
	{
		if (strcmp(tmp, "\n") == 0)
		{
			break;
		}
	}

	char method[N], path[N], protocol[N];

	if (sscanf(line, "%[^ ] %[^ ] %[^ ]", method, path, protocol) != 3)
	{
		send_err(500,"error","sscanf error");
	}

					#if debug
						puts(method);
						puts(path);
						puts(protocol);

					#endif // debug
	if (strcmp("GET", method) != 0||path[0]!='/')
	{
		send_err(500,"error","GET or / error");
	}
	char *file = path + 1;
#if debug
	puts(file);
#endif // debug

	strdecode(file,file);
	
	if(file[0] == '\0')     //   GET / http/1.1  如果这样的时候下边就走不了了所以要改为./
		file="./";
	
	//检测是否为合法的文件格式
	len=strlen(file);
	if(file[0]=='/'	|| strcmp(file,"..") == 0
					|| strncmp(file,"../",3)==0
					|| strncmp(&(file[len-3]),"/.."==0)
					||strstr(file,"/../"!=NULL))
					{
						send_err(400,"error","file strcmp");
					}
 

	struct stat st;
	if (stat(file, &st) < 0)
	{
		send_err(500,"error","stat error");
	}
    //判断file属性,如果是目录就进入一个分支
    if(S_IDDIR(st.st_mode))
    {
        char location[N];
        if(file[len-1]!='/')
        {
            snprintf(location,sizeof(location),"Location:%s",path);
            send_err(302,location,"Location error");
        }
        sned_headers("text/html",-1);
		printf("<html><head><title>Index of %s</title></head>\n<body bgcolor=\"#99cc99\"><h4>Index of %s<h/4>\n<pre>\n",file,file);
			/*
		 *  int scandir(const char *dirp, 
		 *				struct dirent ***namelist,
		 *			    int (*filter)(const struct dirent *),
		 *			    int (*compar)(const struct dirent **, const struct dirent **)
		 *			   );
		 *	依据匹配项目，扫描一个目录
		 *	扫描dirp目录下(不包括子目录)满足filter过滤模式的文件,
		 *  返回的结果是compare函数经过排序的，并保存在namelist中。
		 *  
		 *	scandir() 函数扫描目录 dirp，对每一个目录项（文件名）调用filter()。
		 *	把每一个filter() 返回非零项目保存在一个通过malloc(3) 分配的缓存区里，
		 *	再通过比较函数是compar() 的qsort(3) 函数排序，最后收集在namelist 的数组里，
		 *	这个数组也是通过malloc(3) 分配的。如果filter 是 NULL，所有项目都被选择
		 *
		 *  alphasort和versionsort是使用到的两种排序的函数
		 *
		 *	scandir() 函数返回被选择的目录条数，或者如果出错返回 -1。
		 */
		
		struct dirent **dl;
		int n,i;
		n=scandir(file,&dl,NULL,alphasort);
		if(n<0)
		{
			perror("scandir");
		}else{
			for(i=0;i<n;++i);
				file_infos(file,dl[i]->d_name);
		}		
		printf("</pre>\n<hr>\n<address><a href=\"%s\">%s</a></address>\n</body></html>\n"
		               , "巴拉巴拉", xhttp);
	
    }
	else{
    //否则就打开传送
	FILE *fp = NULL;
	fp=fopen(file, "r");
	if (fp == NULL)
	{
		send_err(500,"error","fopen error");
	}

	//strrchar(filename,'.')//从右往左 到小数点前停下   记录下来   比如 qwe.MP3 =>  .mp3
	char *dot = strrchr(file, '.');
	char *type = NULL;
	
	if (dot == NULL) {
		type = "text/plain; charset=utf-8";
	}
	else if (strcmp(dot, ".html") == 0) {
		type = "text/html; charset=utf-8";
	}
	else if (strcmp(dot, ".jpg") == 0) {
		type = "image/jpeg";
	}
	else if (strcmp(dot, ".gif") == 0) {
		type = "image/gif";
	}
	else if (strcmp(dot, ".png") == 0) {
		type = "image/png";
	}
	else if (strcmp(dot, ".mp3") == 0) {
		type = "audio/mpeg";
	}
	else {
		type = "text/plain; charset=iso-8859-1";
	}

	//报头协议封装函数
	//发送数据
	send_headers(type, st.st_size);
	char ch;
	while ((ch = getc(fp)) != EOF)
		putchar(ch);


	fflush(stdout);
	fclose(fp);

						#if debug
							puts("stat");
							system("pause");
						#endif // debug
	
                        
	return 0;                 
	
	
}
