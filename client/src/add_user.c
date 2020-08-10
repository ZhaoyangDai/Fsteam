#include "client.h"

/*************************************************
Function: 		login_root 			// 函数名称
Description:  	管理员登录界面函数	// 函数功能、性能等的描述
Calls: 			add_user，dele_user, // 被本函数调用的函数清单
Called By: 		login_func			// 调用本函数的函数清单
Input: 			socketfd,msg	 	// 输入参数说明
Output: 		socketfd,msg		// 对输出参数的说明
Return: 							// 函数返回值的说明
Others: 							// 其它说明
*************************************************/

void add_user(int socketfd,MSG *msg)
{
/*	
	int ret;
	printf("请输入用户名：\n");
	scanf("%s",msg->username);
	getchar();
	printf("请输入密码：\n");
	scanf("%s",msg->passwd);
	getchar();
	printf("请输入姓名：\n");
	scanf("%s",msg->name);
	getchar();
	printf("请输入性别：\n");
	scanf("%s",msg->sex);
	getchar();
	printf("请输入年龄：\n");
	scanf("%d",&msg->age);
	getchar();
	printf("请输入手机号：\n");
	scanf("%s",msg->phone);
	getchar();
	printf("请输入地址：\n");
	scanf("%s",msg->addr);
	getchar();
	//发送信息
	ret = send(socketfd, msg, sizeof(MSG),0);
	if(ret < 0){
		perror("reg send error\n");
		exit(1);
	}
	//接受信息
	ret = recv(socketfd, msg, sizeof(MSG),0);
	if(ret < 0){
		perror("reg recv error\n");
		exit(1);
	}
	if(msg->flags[0] == REG_SUC){
		printf("添加成功！\n");
	}else
		printf("添加失败！\n");
*/
	register_func(socketfd,msg);
	return;
	
}
