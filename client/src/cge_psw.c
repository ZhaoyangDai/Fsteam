#include "client.h"

/*************************************************
Function: 		cge_psw 			// 函数名称
Description:  	修改密码函数		// 函数功能、性能等的描述
Calls: 			cge_psw 		 	// 被本函数调用的函数清单
Called By: 		login_user			// 调用本函数的函数清单
Input: 			socketfd,msg	 	// 输入参数说明
Output: 							// 对输出参数的说明
Return: 							// 函数返回值的说明
Others: 							// 其它说明
 *************************************************/

void cge_psw(int socketfd,MSG *msg)
{
	int ret;	
	/*
	printf("请输入要修改您的工号：\n");
	scanf("%d",&msg->id);
	getchar();
	*/
	
	//输入密码
	printf("请输入修改后的密码：\n");
	scanf("%s",msg->passwd);
	getchar();
	
	//发送
	ret = send(socketfd,msg,sizeof(MSG),0);
	if(ret < 0){
		perror("cge_user send error\n");
		exit(1);
	}

	//接受
	ret = recv(socketfd,msg,sizeof(MSG),0);
	if(ret < 0){
		perror("cge_user recv error\n");
		exit(1);
	}

	if(msg->flags[0] == CGE_SUC){
		printf("修改成功！\n");
	}else
		printf("修改失败！\n");
	
	return;
}

