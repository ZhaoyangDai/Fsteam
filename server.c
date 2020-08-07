#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <errno.h>
#include <netinet/in.h>
#include <netinet/ip.h>

#define BACKLOG 30

/***********************************
 * 监听函数
 * 功能：通过接口监听
 * 参数：端口号
 *       监听数
 * 返回值：成功返回 0
 * 	 	   失败返回-1
 *
 * *********************************/
int listen_socket(const unsigned int port,int backlog ){

	socklen_t b_len = sizeof(int);
	int b_reuse = 1;

	/*创建套接字*/
	int sockfd = -1;
	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd < 0){
		perror("socket create error");
		return -1;
	}
	/*允许快速重用*/
	if(0 != setsockopt(sockfd,SOL_SOCKET,SO_REUESADDR,\
				(void *)&b_reuse,b_len)){
		perror("reuse error");
		exit(1);
	}

	/*定义并填充结构体信息*/
	struct sockaddr_in saddr = {
		.sin_family = AF_INET,
		.sin_port = htons(port),
		.sin_addr.s_addr = INADDR_ANY,
	};

	/*绑定地址*/
	if(0 !=  bind(sockfd,(struct sockaddr *)&saddr,sizeof (saddr))){
		perror("bind error");
		exit(1);
	}

	/*监听*/
	if(0 != listen(sockfd,BACKLOG)){
		perror("listen error");
		exit(1);
	}
	printf("server begin work !\n");
	return sockfd;
}

int main(int argc, const char *argv[])
{
	struct sockaddr_in caddr;
	int sockfd = listen_socket(port,BACKLOG);
	unsigned short port = 99999;
	char buf[BUFSIZ];

	if(2 == argc){
		port = atoi(argv[1]);
	}

	/*调用监听函数，监听服务器*/
	if(0 > sockfd){
		perror("server is leave.\n");
		return 0;
	}
	printf("wait for a client.\n");

	/*接受客户端请求*/
	rwsockfd = accept(sockfd,(struct sockaddr *)caddr,sizeof(caddr))
		if(0 > rwsockfd){
			perror("accept error");
			exit(1);
		}

	/****************************
	 *判断客户端是否有数据传递
	 *如果产生数据传递，执行接收
	 ****************************/


	/*接收客户端指令*/
	bzero(&buf,sizeof(buf));
	recvCmd = recv(rwsockfd,buf,sizeof(buf),0);
	if(recvCmd <= 0){
		perror("recv error");
		return -1;
	}
	/*发送数据到客户端*/
	if(0 >= send(rwsockfd,buf,sizeof(buf),0)){
		perror("send error");
		return -1;
	}

	close(sockfd);
	close(rwsockfd)
		return 0;
}
