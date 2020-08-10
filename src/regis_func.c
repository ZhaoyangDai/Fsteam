#include "client.h"

void regis_func(DATA *command,int sockfd)
{
	int ret;
	command->protocol = CLI_REGIS;//请求注册
	name_func(command->data.username);//判断输入的用户名是否合法
	psw_func(command->data.userpsw);//判断输入的密码是否合法
	printf("请输入名字：\n");
	scanf(" %s\n",&command->data.info.name);
	printf("请输入年龄：\n");
	scanf(" %d\n",&command->data.info.age);
	printf("请输入性别：(man,woman)\n");
	scanf(" %s\n",&command->data.info.sex);

	//发送数据
	ret = send(sockfd,command,sizeof(DATA),0);
	if(ret < 0 ){
		perror("regis_func send error\n");
		exit(1);
	}
	//接收数据
	memset(command,0,sizeof(DATA));
	ret = recv(sockfd,0,sizeof(DATA),0);
	if(ret < 0){
		perror("regis_func recv error\n");
		exit(1);
	}
	if(command->protocol == REGIS_SUC){
		printf("注册成功！\n");
	}else{
		printf("注册失败！\n");
		exit(1);
	}
}
