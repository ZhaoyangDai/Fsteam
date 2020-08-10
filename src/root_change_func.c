#include "client.h"

void cge_salary_func(DATA *command,int sockfd)
{
	int ret;
	//修改标志位：修改工资
	command->protocol = LOG_CGE_SAL;
	//获取修改的年龄
	printf("请输入工资：\n");
	scanf("%d\n",&command->data.info.salary);
	getchar();
	//发送信息结构体
	ret = send(sockfd,command,sizeof(DATA),0);
	if(ret < 0){
		perror("cge_salary_func send error\n");
		exit(1);
	}
	//接收信息结构体
	memset(command,0,sizeof(DATA));
	ret = recv(sockfd,command,sizeof(DATA),0);
	if(ret < 0){
		perror("cge_salary_func recv error\n");
		exit(1);
	}
	if(command->protocol == CGE_SAL_OK){
		printf("修改工资成功！\n");
	}else{
		printf("修改工资失败！\n");
	}
}

void cge_dep_func(DATA *command,int sockfd)
{	
	int ret;
	//修改标志位：修改部门
	command->protocol = LOG_CGE_DEP;
	//获取修改的部门
	printf("请输入部门：\n");
	scanf("%s\n",&command->data.info.department);
	getchar();
	//发送信息结构体
	ret = send(sockfd,command,sizeof(DATA),0);
	if(ret < 0){
		perror("cge_dep_func send error\n");
		exit(1);
	}
	//接收信息结构体
	memset(command,0,sizeof(DATA));
	ret = recv(sockfd,command,sizeof(DATA),0);
	if(ret < 0){
		perror("cge_dep_func recv error\n");
		exit(1);
	}
	if(command->protocol == CGE_DEP_OK){
		printf("修改部门成功！\n");
	}else{
		printf("修改部门失败！\n");
	}
}

void cge_tele_func(DATA *command,int sockfd)
{	
	int ret;
	//修改标志位：修改电话
	command->protocol = LOG_CGE_TELE;
	//获取修改的电话
	printf("请输入电话：\n");
	scanf("%s\n",&command->data.info.telephone);
	getchar();
	//发送信息结构体
	ret = send(sockfd,command,sizeof(DATA),0);
	if(ret < 0){
		perror("cge_tele_func send error\n");
		exit(1);
	}
	//接收信息结构体
	memset(command,0,sizeof(DATA));
	ret = recv(sockfd,command,sizeof(DATA),0);
	if(ret < 0){
		perror("cge_tele_func recv error\n");
		exit(1);
	}
	if(command->protocol == CGE_TELE_OK){
		printf("修改电话成功！\n");
	}else{
		printf("修改电话失败！\n");
	}
}

void cge_mail_func(DATA *command,int sockfd)
{
	int ret;
	//修改标志位：修改邮箱
	command->protocol = LOG_CGE_MAIL;
	//获取修改的邮箱
	printf("请输入邮箱：\n");
	scanf("%s\n",&command->data.info.E_mail);
	getchar();
	//发送信息结构体
	ret = send(sockfd,command,sizeof(DATA),0);
	if(ret < 0){
		perror("cge_,mail_func send error\n");
		exit(1);
	}
	//接收信息结构体
	memset(command,0,sizeof(DATA));
	ret = recv(sockfd,command,sizeof(DATA),0);
	if(ret < 0){
		perror("cge_mail_func recv error\n");
		exit(1);
	}
	if(command->protocol == CGE_MAIL_OK){
		printf("修改邮箱成功！\n");
	}else{
		printf("修改邮箱失败！\n");
	}
}

void cge_addr_func(DATA *command,int sockfd)
{
	int ret;
	//修改标志位：修改地址
	command->protocol = LOG_CGE_ADDR;
	//获取修改的地址
	printf("请输入地址：\n");
	scanf("%s\n",&command->data.info.address);
	getchar();
	//发送信息结构体
	ret = send(sockfd,command,sizeof(DATA),0);
	if(ret < 0){
		perror("cge_addr_func send error\n");
		exit(1);
	}
	//接收信息结构体
	memset(command,0,sizeof(DATA));
	ret = recv(sockfd,command,sizeof(DATA),0);
	if(ret < 0){
		perror("cge_addr_func recv error\n");
		exit(1);
	}
	if(command->protocol == CGE_ADDR_OK){
		printf("修改地址成功！\n");
	}else{
		printf("修改地址失败！\n");
	}
}

void root_change_func(DATA *command,int sockfd)
{

	char buf[10];
	while(1)
	{
		//将对应工号的信息显示
		root_info_func(command,sockfd);

		//显示页面	
		printf("*******************\n");
		printf("*1. 修改名字      *\n");
		printf("*2. 修改年龄      *\n");
		printf("*3. 修改性别      *\n");
		printf("*4. 修改密码      *\n");
		printf("*5. 修改工资      *\n");
		printf("*6. 修改部门      *\n");
		printf("*7. 修改电话      *\n");
		printf("*8. 修改邮箱      *\n");
		printf("*9. 修改地址      *\n");
		printf("*10. 退出         *\n");
		printf("*******************\n");
		printf("请选择：\n");
		//判断输入选择
		memset(buf,0,sizeof(buf));
		fgets(buf,sizeof(buf),stdin);
		buf[strlen(buf)-1] == '\0';
		if((strcmp("1",buf)) == 0){
			//修改名字函数
			cge_name_func(command,sockfd);
		}else if((strcmp("2",buf)) == 0){
			//修改年龄函数
			cge_age_func(command,sockfd);
		}else if((strcmp("3",buf)) == 0){
			//修改性别函数
			cge_sex_func(command,sockfd);	
		}else if((strcmp("4",buf)) == 0){
			//修改密码函数
			cge_psw_func(command,sockfd);
		}else if((strcmp("5",buf)) == 0){
			//修改工资函数
			cge_salary_func(command,sockfd);
		}else if((strcmp("6",buf)) == 0){
			//修改部门函数
			cge_dep_func(command,sockfd);
		}else if((strcmp("7",buf)) == 0){
			//修改电话函数
			cge_tele_func(command,sockfd);
		}else if((strcmp("8",buf)) == 0){
			//修改邮箱函数
			cge_mail_func(command,sockfd);
		}else if((strcmp("9",buf)) == 0){
			//修改地址函数
			cge_addr_func(command,sockfd);
		}else if((strcmp("10",buf)) == 0){
			break;
		}else{
			printf("输入错误!\n");
		}
	}
}
