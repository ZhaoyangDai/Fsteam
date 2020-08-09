#include "client.h"


void cge_psw_func(DATA *command,int sockfd)
{
	int ret;
	//修改标志位：修改密码
	command->protocol = LOG_CGE_PSW;
	memset(command->data.userpsw,0,sizeof(command->data.userpsw));
	psw_func(command->data.userpsw);

	//发送信息结构体
	ret = send(sockfd,command,sizeof(DATA),0);
	if(ret < 0){
		perror("change_func send error\n");
		return -1;
	}
	//接受信息结构体
	memset(command,0,sizeof(command));
	ret = recv(sockfd,command,sizeof(DATA),0);
	if(ret < 0){
		perror("change_func send error\n");
		return -1;
	}
	if(command->protocol == CGE_PSW_OK){
		printf("修改密码成功\n");
	}else{
		printf("修改密码失败\n");
	}
}

void cge_name_func(DATA *command,int sockfd)
{
	int ret;
	//修改标志位：修改姓名
	command->protocol = LOG_CGE_NAME;
	//获取修改的名字
	printf("请输入名字：\n");
	scanf("%s\n",&command->data.info.name);
	getchar();
	//发送信息结构体
	ret = send(sockfd,command,sizeof(DATA),0);
	if(ret < 0){
		perror("cge_name_func send error\n");
		return -1;
	}
	//接收信息结构体
	memset(command,0,sizeof(DATA));
	ret = recv(sockfd,command,sizeof(DATA),0);
	if(ret < 0){
		perror("cge_name_func recv error\n");
		return -1;
	}
	if(command->protocol == CGE_NAME_OK){
		printf("修改名字成功！\n");
	}else{
		printf("修改名字失败！\n");
	}

}

void cge_age_func(DATA *command,int sockfd)
{	
	int ret;
	//修改标志位：修改年龄
	command->protocol = LOG_CGE_AGE;
	//获取修改的年龄
	printf("请输入年龄：\n");
	scanf("%d\n",&command->data.info.age);
	getchar();
	//发送信息结构体
	ret = send(sockfd,command,sizeof(DATA),0);
	if(ret < 0){
		perror("cge_age_func send error\n");
		return -1;
	}
	//接收信息结构体
	memset(command,0,sizeof(DATA));
	ret = recv(sockfd,command,sizeof(DATA),0);
	if(ret < 0){
		perror("cge_age_func recv error\n");
		return -1;
	}
	if(command->protocol == CGE_AGE_OK){
		printf("修改年龄成功！\n");
	}else{
		printf("修改年龄失败！\n");
	}
}

void cge_sex_func(DATA *command,int sockfd)
{	
	int ret;
	//修改标志位：修改性别
	command->protocol = LOG_CGE_SEX;
	//获取修改的性别
	printf("请输入性别：(man,woman)\n");
	scanf("%s\n",&command->data.info.sex);
	getchar();
	//发送信息结构体
	ret = send(sockfd,command,sizeof(DATA),0);
	if(ret < 0){
		perror("cge_sex_func send error\n");
		return -1;
	}
	//接收信息结构体
	memset(command,0,sizeof(DATA));
	ret = recv(sockfd,command,sizeof(DATA),0);
	if(ret < 0){
		perror("cge_sex_func recv error\n");
		return -1;
	}
	if(command->protocol == CGE_SEX_OK){
		printf("修改性别成功！\n");
	}else{
		printf("修改性别失败！\n");
	}
}



void cge_info_func(DATA *command,int sockfd)
{
	char buf[10];
	while(1)
	{
		//显示页面
		printf("*******************\n");
		printf("*1. 修改登录密码  *\n");
		printf("*2. 修改个人信息  *\n");
		printf("*3. 退出          *\n");
		printf("*******************\n");
		printf("请选择：\n");
		//判断输入选择
		memset(buf,0,sizeof(buf));
		fgets(buf,sizeof(buf),stdin);
		buf[strlen(buf)-1] = '\0';
		if((strcmp("1",buf)) == 0){
			cge_psw_func(command,sockfd);
		}else if(strcmp("2",buf) == 0){
			//修改个人信息
			while(1)
			{
				//显示页面
				printf("*******************\n");
				printf("*1. 修改姓名      *\n");
				printf("*2. 修改年龄      *\n");
				printf("*3. 修改性别      *\n");
				printf("*4. 退出          *\n");

				//判断输入选择
				memset(buf,0,sizeof(buf));
				fgets(buf,sizeof(buf),stdin);
				buf[strlen(buf)-1] = '\0';
				if((strcmp("1",buf)) == 0){
					cge_name_func(command,sockfd);
				}else if((strcmp("2",buf)) == 0){
					cge_age_func(command,sockfd);
				}else if((strcmp("3",buf)) == 0){
					cge_sex_func(command,sockfd);
				}else if((strcmp("4",buf))== 0){
					break;
				}else{
					printf("输入错误！\n");
				}
			}
		}else if((strcmp("3")) == 0){
			break;
		}else{
			printf("输入错误！\n");
		}

	}
}

