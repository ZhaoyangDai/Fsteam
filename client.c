/***************************************************
 * Name:       client.c
 * Data:       2020.8.7
 * Description:主函数
 * Author:     shilei
 *
 * ************************************************/

#include "client.h"

#define CLI_LOGIN 		1 	//客户端请求登录
#define LOG_SUC 		2 	//登录成功
#define LOG_QUIT 		3 	//登录退出
#define LOG_SHW_INF 	4 	//查看个人信息
#define LOG_CGE_PSW 	5 	//修改密码
#define CGE_PSW_OK 		6 	//修改密码成功
#define LOG_CGE_NAME 	7 	//修改名字
#define CGE_NAME_OK 	8 	//修改名字成功
#define LOG_CGE_YEAR 	9 	//修改年龄
#define CGE_YEAR_OK  	10 	//修改年龄成功
typedef struct
{
	char name[20];
	char sex[10];
	int year;
	double salary;
	char department[20];
	double telephone;
	char E_mail[30];
	char address[100];
	char history[50];
}empinfo_t;

typedef struct
{
	char username[20];
	char userpsw[20];
	empinfo_t info;
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
		command->protocol = CLI_LOGIN;//请求登录
		
		//发送数据
		ret = send(sockfd,command,sizeof(DATA),0);
		if(ret < 0 ){
			perror("client send error\n");
			return -1;
		}
		memset(command,0,sizeof(DATA))；
		ret = recv(sockfd,0,sizeof(DATA),0);
		if(ret < 0){
			perror("recv error\n");
			return -1;
		}
		if(command->protocol == LOG_SUC){
			login_func(command,sockfd);
		}else{
			printf("登录失败！\n");
			return -1;
		}
	}
	free(command);
	close(sockfd);
	return 0;
}
