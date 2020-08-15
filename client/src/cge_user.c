#include "client.h"


/*************************************************
Function: 		login_root 			// 函数名称
Description:  	修改信息函数	// 函数功能、性能等的描述
Calls: 								 // 被本函数调用的函数清单
Called By: 		login_root			// 调用本函数的函数清单
Input: 			socketfd,msg	 	// 输入参数说明
Output: 		socketfd,msg		// 对输出参数的说明
Return: 							// 函数返回值的说明
Others: 							// 其它说明
 *************************************************/

void cge_user(int socketfd,MSG *msg)
{
	int ret;
	printf("请输入要修改用户的工号：\n");
	scanf("%d",&msg->id);
	getchar();

	printf("请输入年龄：\n");
	scanf("%d",&msg->age);
	getchar();

	printf("请输入电话：\n");
	scanf("%s",msg->phone);
	getchar();

	printf("请输入地址：\n");
	scanf("%s",msg->addr);
	getchar();

	ret = send(socketfd,msg,sizeof(MSG),0);
	if(ret < 0){
		perror("cge_user send error\n");
		exit(1);
	}
	
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
