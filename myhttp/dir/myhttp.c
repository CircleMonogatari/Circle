//#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#define N 1024
#define __err send_err(500,"error","我懒所以没写")
#define __linux 1


void send_headers(char *type, off_t length)//发送协议头文件
{
	printf("%s %d %s\r\n", "HTTP/1.1", 200, "0k");
	printf("Content-Type:%s\r\n", type);
#if __linux
	printf("Content-Length:%ld\r\n", (int64_t)length);
#endif // __linux
	printf("Connection: close\r\n");
	printf("\r\n");
}

void send_err(int status,char *title,char *text)//发送错误
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

int main(int argc,char *argv[]) {

#if __linux
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
#else
	if (argv[1] == NULL)
		argv[1] = "/home/itheima/myhttp";

#endif // __linux
	char line[N];
	char tmp[N];

	if (fgets(line, N, stdin) == 0)
	{
		send_err(500,"error","get line error");
	}

					#if debug
						puts(line);
					#endif
	

	while (fgets(tmp, N, stdin))
	{
		#if __linux
		if (strcmp(tmp, "\n") == 0)
		{
			break;
		}
		#else
		if (strcmp(tmp, "\n") == 0)
		{
			break;
		}
		#endif // __linux
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

	struct stat st;
	if (stat(file, &st) < 0)
	{
		send_err(500,"error","stat error");
	}

	FILE *fp = NULL;
	fp=fopen(file, "r");
	if (fp == NULL)
	{
		send_err(500,"error","fopen error");
	}

	//strrchar(filename,'.')//从右往左 到小数点前停下   记录下来   比如 qwe.MP3 =>  mp3
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