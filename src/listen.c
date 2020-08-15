#include "server.h"

/*********************************************************
 * Function Name  : listen_socket
 * Description 	  : listen client is connect
 * Input          : port ,backlog
 * Output         : fd
 * Return         : None
 * *******************************************************/
int listen_socket(const unsigned int port,int backlog )
{

	int fd = -1;
	int b_reuse = 1;

	/*创建套接字*/
	fd = socket(AF_INET,SOCK_STREAM,0);
	if(0 > fd)
	{
		perror("socket create error");
		return -1;
	}

	/*允许快速重用*/
	if(0 > setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,\
				(void *)&b_reuse,sizeof(int)))
	{
		perror("reuse error");
		return -1;
	}

	/*填充地址信息结构体*/
	struct sockaddr_in sin = 
	{
		.sin_family 	 = AF_INET,
		.sin_port 		 = htons(port),
		.sin_addr.s_addr = INADDR_ANY,
	};

	/*绑定地址*/
	if(0 >  bind(fd,(struct sockaddr *)&sin,sizeof (sin)))
	{
		perror("bind error");
		return -1;
	}

	/*监听*/
	if(0 > listen(fd,BACKLOG))
	{
		perror("listen error");
		return -1;
	}
	printf("server begin working ...\n");
	return fd;
}

