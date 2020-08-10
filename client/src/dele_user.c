#include "client.h"


/*************************************************
Function: 		login_root 			// 函数名称
Description:  	删除用户函数	// 函数功能、性能等的描述
Calls: 								 // 被本函数调用的函数清单
Called By: 		login_func			// 调用本函数的函数清单
Input: 			socketfd,msg	 	// 输入参数说明
Output: 		socketfd,msg		// 对输出参数的说明
Return: 							// 函数返回值的说明
Others: 							// 其它说明
 *************************************************/
void dele_user(int socketfd,MSG *msg)
{
	int ret;
	printf("请输入要删除用户的工号：\n");
	scanf("%d",&msg->id);
	getchar();

	ret = send(socketfd, msg, sizeof(MSG),0);
	if(ret < 0){
		perror("dele_user send error\n");
		exit(1);
	}
	ret = recv(socketfd, msg,sizeof(MSG),0);
	if(ret < 0){
		perror("dele_user recv error\n");
		exit(1);
	}
	if(msg->flags[0] == DELE_SUC){
		printf("删除用户成功！\n");
	}else
		printf("删除用户失败！\n");

	return;
}
