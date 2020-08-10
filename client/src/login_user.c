#include "client.h"


/*************************************************
Function: 		login_user 			// 函数名称
Description:  	用户登录后显示函数	// 函数功能、性能等的描述
Calls: 			inq_info,cge_user 	// 被本函数调用的函数清单
				cge_psw
Called By: 		login_func			// 调用本函数的函数清单
Input: 			socketfd,msg	 	// 输入参数说明
Output: 		socketfd,msg		// 对输出参数的说明
Return: 							// 函数返回值的说明
Others: 							// 其它说明
 *************************************************/
void login_user(int socketfd,MSG *msg)
{
	int n;
	while(1)
	{
		printf("*****************\n");                                          
		printf("*1. 查询个人信息*\n");
		printf("*2. 修改个人信息*\n");
		printf("*3. 修改密码    *\n");
		printf("*4. 退出        *\n");
		printf("*****************\n");
		printf("请选择：\n");
		//获得选择
		scanf("%d",&n);
		getchar();

		switch(n){
		case 1:
			//发送"查询"
			msg->flags[0] = INQ_INFO;
			send(socketfd, msg, sizeof(MSG),0);	
			inq_info(socketfd,msg);
			break;
		case 2:	
			//发送"修改信息"
			msg->flags[0] = CGE_USER;
			send(socketfd, msg, sizeof(MSG),0);
			cge_user(socketfd,msg);
			break;
		case 3:
			//发送"修改密码"
			msg->flags[0] = CGE_PSW;
			send(socketfd, msg, sizeof(MSG),0);
			cge_psw(socketfd,msg);
			break;
		case 4:	
			msg->flags[0] = QUIT;
			send(socketfd, msg, sizeof(MSG),0);
			return;	
		default:
			printf("输入错误！\n");
			break;
		}
	}
}

