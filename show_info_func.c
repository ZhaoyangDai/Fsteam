#include "client.c"

void show_info_func(DATA *command,int sockfd)
{
	int ret;
	//发送标志位：查看个人信息
	command->protocol = LOG_SHW_INF;
	ret = send(sockfd,command,sizeof(DATA),0);
	if(ret < 0){
		perror("show_info_func send is error\n");
		return -1;
	}
	//接受信息结构体
	memset(command,0,sizeof(DATA));
	ret = recv(sockfd,command,sizeof(DATA),0);
	if(ret < 0){
		perror("show_info_func recv error\n");
		return -1;
	}
	//打印个人信息
	printf("姓名：%s\n",command->data.info.name);
	printf("工资：%s\n",command->data.info.salary);
	printf("部门：%s\n",command->data.info.department);
	printf("电话：%s\n",command->data.info.telephone);
	printf("邮箱：%s\n",command->data.info.E_mail);
	printf("地址：%s\n",command->data.info.address);
}

