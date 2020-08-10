#include "client.h"

/*************************************************
Function: 		login_func 			// 函数名称
Description:  	登录函数			// 函数功能、性能等的描述
Calls: 			login_root,login_user 	// 被本函数调用的函数清单
Called By: 		client				// 调用本函数的函数清单
Input: 			socketfd,msg	 	// 输入参数说明
Output: 		socketfd,msg		// 对输出参数的说明
Return: 							// 函数返回值的说明
Others: 							// 其它说明
*************************************************/


void login_func(int socketfd,MSG *msg)
{
	int ret;
	printf("请输入用户名：\n");
	scanf("%s",msg->username);
	getchar();
	printf("请输入密码：\n");
	scanf("%s",msg->passwd);
	getchar();
		//接收
	ret = send(socketfd, msg, sizeof(MSG),0);
	if(ret < 0){
		perror("login_func send error\n");
		exit(1);
	}
	//发送
	ret = recv(socketfd, msg, sizeof(MSG),0);
	if(ret < 0){
		perror("login_func send error\n");
		exit(1);
	}
	if(msg->flags[0] == LOGIN_SUC){
		printf("登录成功！\n");
		//从服务端返回的结构体中的type判断
		//是否是管理员
		if(msg->type[0] == 0){
			login_root(socketfd, msg);
		}else{
			login_user(socketfd, msg);
		}
	}else
		printf("登录失败！\n");
}
