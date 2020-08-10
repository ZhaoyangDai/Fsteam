#include "client.h"
void net_init(const char *argv[])
{
	if((socketfd = socket(AF_INET, SOCK_STREAM, 0 )) < 0){                      
		perror("fail to socket");   
		exit(-1);
	}   
	bzero(&serveraddr, sizeof(serveraddr));

	//网络信息结构体填充
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr(argv[1]);
	serveraddr.sin_port = htons(atoi(argv[2]));
	//连接
	if(connect(socketfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0){
		perror("fail to connect");  
		close(socketfd);
		exit(-1);
	}   
}
