#include "client.h"


/*************************************************
Function: 		inq_his 			// 函数名称
Description:  	查询历史记录函数	// 函数功能、性能等的描述
Calls: 			inq_his 			 // 被本函数调用的函数清单
Called By: 		login_root			// 调用本函数的函数清单
Input: 			socketfd,msg	 	// 输入参数说明
Output: 		socketfd,msg		// 对输出参数的说明
Return: 							// 函数返回值的说明
Others: 							// 其它说明
 *************************************************/

void inq_his(int socketfd,MSG *msg)
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
	printf("工号%d员工的历史记录为：",msg->id);

}
