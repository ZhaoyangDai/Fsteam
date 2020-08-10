
#include "client.h"

/*************************************************
Function: 		inq_info 			// 函数名称
Description:  	查询信息函数		// 函数功能、性能等的描述
Calls: 			inq_info 			 // 被本函数调用的函数清单
Called By: 		login_root			// 调用本函数的函数清单
Input: 			socketfd,msg	 	// 输入参数说明
Output: 		msg					// 对输出参数的说明
Return: 							// 函数返回值的说明
Others: 							// 其它说明
 *************************************************/
void inq_info(int socketfd, MSG *msg)
{
	int ret;
	printf("请输入要查询用户的工号");
	scanf("%d",&msg->id);
	getchar();

	ret = send(socketfd,msg,sizeof(MSG),0);
	if(ret < 0){
		perror("inq_info send error\n");
		exit(1);
	}

	ret = recv(socketfd,msg,sizeof(MSG),0);
	if(ret < 0){
		perror("inq_info recv error\n");
		exit(1);
	}
	printf("工号：%d\n",msg->id);
	printf("姓名：%s\n",msg->name);
	printf("性别：%s\n",msg->sex);
	printf("年龄：%d\n",msg->age);
	printf("手机号：%s\n",msg->phone);
	printf("地址：%s\n",msg->addr);
	return;

}
