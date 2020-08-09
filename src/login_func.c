#include "client.h"

void login_func(DATA *command, int sockfd)
{
	int ret;
	char buf[10];

	while(1)
	{
		//功能界面
		printf("*******************\n");
		printf("*1. 查询个人信息  *\n");
		printf("*2. 修改密码      *\n");
		printf("*3. 修改个人信息  *\n");
		printf("*4. 查询历史记录  *\n");
		printf("*5. 退出          *\n");
		printf("请选择：\n");
		memset(buf,0,sizeof(buf));
		fgets(buf,sizeof(buf),stdin);
		buf[strlen(buf)-1] = '\0';
		//选择判断
		if((strcmp("1",buf)) == 0){
			//查看信息函数
			show_info_func(command,sockfd);
		}
		else if((strcmp("2",buf)) == 0){
			//修改密码函数
			cge_psw_func(command,sockfd);		
		}
		else if((strcmp("3",buf)) == 0){
			//修改个人信息函数
			cge_info_func(command,sockfd);
		}
		else if((strcmp("4",buf)) == 0){
			//查看历史信息函数
			show_his_func(command,sockfd);
		}	
		else if((strcmp("5",buf)) == 0){
			//退出，返回状态登录退出，并发送信息结构体
			command->protocol = LOG_QUIT;
			ret = send(sockfd,command,sizeof(DATA),0);
			if(ret < 0){
				perror("login_func send is error\n");
				free(command);
				close(sockfd);
				return -1;
			}
		}else{
			printf("输入错误！\n");
			return -1;
		}
	}
}

void root_login_func(DATA *command, int sockfd)
{
	int ret;
	char buf[10];

	while(1)
	{
		//功能界面
		printf("*******************\n");
		printf("*1. 添加用户      *\n");
		printf("*2. 删除用户      *\n");
		printf("*3. 修改用户信息  *\n");
		printf("*4. 查询用户信息  *\n");
		printf("*5. 查询历史记录  *\n");
		printf("*6. 退出          *\n");
		printf("请选择：\n");
		memset(buf,0,sizeof(buf));
		fgets(buf,sizeof(buf),stdin);
		buf[strlen(buf)-1] = '\0';
		//选择判断
		if((strcmp("1",buf)) == 0){
			//添加用户函数
			add_user_func(command,sockfd);
		}
		else if((strcmp("2",buf)) == 0){
			//删除用户函数
			delete_user_func(command,sockfd);		
		}
		else if((strcmp("3",buf)) == 0){
			//修改用户信息函数
			root_change_func(command,sockfd);
		}
		else if((strcmp("4",buf)) == 0){
			//查询用户信息函数
			root_info_func(command,sockfd);
		}
		else if((strcmp("5",buf)) ==0){
			//查询用户历史记录函数
			root_his_func(command,sockfd);
		}	
		else if((strcmp("6",buf)) == 0){
			//退出，返回状态登录退出，并发送信息结构体
			command->protocol = LOG_QUIT;
			ret = send(sockfd,command,sizeof(DATA),0);
			if(ret < 0){
				perror("root_login_func send is error\n");
				free(command);
				close(sockfd);
				return -1;
			}
		}else{
			printf("输入错误！\n");
			return -1;
		}
	}
}
