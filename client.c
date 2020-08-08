/***************************************************
 * Name:       client.c
 * Data:       2020.8.7
 * Description:主函数
 * Author:     shilei
 *
 * ************************************************/

#include "client.h"
#ifndef __MY_STRUCT__
#define __MY_STRUCT__

typedef struct
{
	char name[20];
	double salary;
	char department[20];
	double telephone;
	char E_mail[30];
	char address[100];
	char history[50];
}EmpMsg;

typedef struct
{
	char username[20];
	char userpsw[20];
	EmpMsg info;
}data_t;

typedef struct
{
	int protocol;//命令位
	data_t data;
}DATA;


struct sockaddr_in sockaddr;
/*
 *1.创建套接字
 *2.初始化客户端与服务器连接函数
 *
 */
int net(void)
{
	int sockfd,ret;
	//创建网络套接字
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0) < 0)){
		perror("socket is error\n");
		return -1;
	}
	//连接服务器
	ret = connect(sockfd, (struct sockaddr *)&sockaddr,sizeof(sockaddr));
	if(ret < 0){
		perror("connect is error\n");
		return -1;
	}
	return sockfd;
}
int main(int argc, const char *argv[])
{
	int sockfd,ret;
	DATA *command;//初始化信息结构体
	command = (DATA *)malloc(sizeof(DATA));
	if(command == NULL){
		perror("malloc error\n");
		return -1;
	}
	//判断命令行传参是否错误
	if(argc != 3){
		printf("%s server ip\n",argv[0]);
		return -1;
	}
	//清零结构体
	memset(&sockaddr,0,sizeof(sockaddr));
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_addr.s_addr = inet_addr(argv[1]);
	sockaddr.sin_port = htons(atoi(argv[2]));
	
	sockfd = net();

	while(1)
	{
		printf("员工管理系统\n");
		memset(command,0,sizeof(DATA));
		name_func(command->data.username);//判断输入的用户名是否合法
		psw_func(command->data.userpsw);//判断输入的密码是否合法
		command->protocol = 1;//请求登录
		
		//发送数据
		ret = send(sockfd,command,sizeof(DATA),0);
		if(ret < 0 ){
			perror("send error\n");
			return -1;
		}
		memset(command,0,sizeof(DATA))；
		ret = recv(sockfd,0,sizeof(DATA),0);
		if(ret < 0){
			perror("recv error\n");
			return -1;
		}
		if(command->protocol == "登录成功"){
		
		}else{
			printf("登录失败！\n");
			return -1;
		}
	}

	return 0;
}
