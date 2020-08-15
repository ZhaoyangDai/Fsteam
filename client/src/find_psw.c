#include "client.h"

/*************************************************
Function: 		find_psw 			// 函数名称
Description:  	忘记密码函数		// 函数功能、性能等的描述
Calls: 							 	// 被本函数调用的函数清单
Called By: 		client 				// 调用本函数的函数清单
Input: 			psw	 				// 输入参数说明
Output: 		socketfd,msg		// 对输出参数的说明
Return: 							// 函数返回值的说明
Others: 							// 其它说明
 *************************************************/

void find_psw(int socketfd, MSG *msg)
{
	int ret;	
	//校验用户名和工号
	printf("请输入用户名：\n");
	scanf("%s",msg->username);
	getchar();
	printf("请输入工号：\n");
	scanf("%d",&msg->id);
	getchar();

	//发送
	ret = send(socketfd, msg, sizeof(MSG),0);
	if(ret < 0){
		perror("find_psw send error\n");
		exit(1);
	}
	//接收
	ret = recv(socketfd, msg,sizeof(MSG),0);
	if(ret < 0){
		perror("find_psw recv error\n");
		exit(1);
	}

	if(msg->flags[0] == CHECK_OK){
		//校验成功，输入新密码
		printf("请输入新密码：\n");
		scanf("%s",msg->passwd);
		getchar();
		//发送
		ret = send(socketfd, msg, sizeof(MSG),0);
		if(ret < 0){
			perror("find_psw send error\n");
			exit(1);
		}
		ret = recv(socketfd, msg,sizeof(MSG),0);
		if(ret < 0){
			perror("find_psw recv error\n");
			exit(1);
		}

		if(msg->flags[0] == CGE_SUC){
			printf("修改成功！\n");
		}else{
			printf("修改失败！\n");
		}

	}else
		printf("用户名和工号错误！\n");


	return;
}

