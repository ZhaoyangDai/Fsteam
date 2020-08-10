#include "client.h"

void show_info_func(DATA *command,int sockfd)
{
	int ret;
	//发送标志位：查看个人信息
	command->protocol = LOG_SHW_INF;
	ret = send(sockfd,command,sizeof(DATA),0);
	if(ret < 0){
		perror("show_info_func send is error\n");
		exit(1);
	}
	//接受信息结构体
	memset(command,0,sizeof(DATA));
	ret = recv(sockfd,command,sizeof(DATA),0);
	if(ret < 0){
		perror("show_info_func recv error\n");
		exit(1);
	}
	//打印个人信息
	printf("姓名：%s\n",command->data.info.name);
	printf("性别：%s\n",command->data.info.sex);
	printf("年龄：%d\n",command->data.info.age);
	printf("工号：%d\n",command->data.info.number);
	printf("工资：%lf\n",command->data.info.salary);
	printf("部门：%s\n",command->data.info.department);
	printf("电话：%s\n",command->data.info.telephone);
	printf("邮箱：%s\n",command->data.info.E_mail);
	printf("地址：%s\n",command->data.info.address);
}

void root_info_func(DATA *command,int sockfd)
{
	int ret;
	//发送标志位：查看个人信息
	command->protocol = LOG_SHW_INF;
	printf("请输入要查询的工号：\n");
	scanf("%lf\n",command->data.info.number);
	ret = send(sockfd,command,sizeof(DATA),0);
	if(ret < 0){
		perror("root_info_func send is error\n");
		exit(1);
	}
	//接受信息结构体
	memset(command,0,sizeof(DATA));
	ret = recv(sockfd,command,sizeof(DATA),0);
	if(ret < 0){
		perror("root_info_func recv error\n");
		exit(1);
	}
	//打印个人信息
	printf("姓名：%s\n",command->data.info.name);
	printf("性别：%s\n",command->data.info.sex);
	printf("年龄：%d\n",command->data.info.age);
	printf("工号：%d\n",command->data.info.number);
	printf("工资：%lf\n",command->data.info.salary);
	printf("部门：%s\n",command->data.info.department);
	printf("电话：%s\n",command->data.info.telephone);
	printf("邮箱：%s\n",command->data.info.E_mail);
	printf("地址：%s\n",command->data.info.address);
}
