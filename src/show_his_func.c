#include "client.h"

void show_his_func(DATA *command,int sockfd)
{
	int ret;
	//发送标志位：显示历史信息
	command->protocol = LOG_SHW_HIS;
	ret = send(sockfd,command,sizeof(DATA),0);  
	if(ret < 0){
		perror("show_his_func send is error\n");
		exit(1);
	}
	//接受信息结构体
	memset(command,0,sizeof(DATA));
	ret = recv(sockfd,command,sizeof(DATA),0);
	if(ret < 0){
		perror("show_info_func recv error\n");
		exit(1);
	}else{
		printf("登录时间：%s\n",command->data.history);
	}
}

void root_his_func(DATA *command,int sockfd)
{
	int ret;
	//发送标志位：显示历史信息
	command->protocol = LOG_SHW_HIS;
	printf("请输入要查询的工号：\n");
	scanf("%d\n",command->data.info.number);
	ret = send(sockfd,command,sizeof(DATA),0);  
	if(ret < 0){
		perror("show_his_func send is error\n");
		exit(1);
	}
	//接受信息结构体
	memset(command,0,sizeof(DATA));
	ret = recv(sockfd,command,sizeof(DATA),0);
	if(ret < 0){
		perror("show_info_func recv error\n");
		exit(1);
	}else{
		printf("登录时间：%s\n",command->data.history);
	}
}
