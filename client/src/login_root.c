#include "client.h"

/*************************************************
Function: 		login_root 			// 函数名称
Description:  	管理员登录界面函数	// 函数功能、性能等的描述
Calls: 			add_user，dele_user, // 被本函数调用的函数清单
 				cge_user,inq_info,inq_his
Called By: 		login_func			// 调用本函数的函数清单
Input: 			socketfd,msg	 	// 输入参数说明
Output: 		socketfd,msg		// 对输出参数的说明
Return: 							// 函数返回值的说明
Others: 							// 其它说明
 *************************************************/

void login_root(int socketfd,MSG *msg)
{
	int n;
	while(1)
	{
		printf("*******************\n");                                           
		printf("*1. 添加用户      *\n");
		printf("*2. 删除用户      *\n");
		printf("*3. 修改用户信息  *\n");
		printf("*4. 查询用户信息  *\n");
//		printf("*5. 查询历史记录  *\n");
		printf("*5. 退出          *\n");
		printf("*******************\n");
		printf("请选择：\n");
		//获取选择
		scanf("%d",&n);
		getchar();
		switch(n){
		case 1:
			//发送"添加用户"
			msg->flags[0] = ADD_USER;
			send(socketfd, msg, sizeof(MSG),0);
			add_user(socketfd,msg);
			break;
		case 2:
			//发送"删除用户"
			msg->flags[0] = DELE_USER;
			send(socketfd, msg, sizeof(MSG),0);
			dele_user(socketfd,msg);
			break;
		case 3:
			//发送"修改用户"
			msg->flags[0] = CGE_USER;
			send(socketfd, msg, sizeof(MSG),0);
			cge_user(socketfd,msg);
			break;
		case 4:
			//发送"查询信息"
			msg->flags[0] = INQ_INFO;
			send(socketfd, msg, sizeof(MSG),0);
			inq_info(socketfd,msg);
			break;
/*		case 5:
			//发送"查询历史"
			msg->flags[0] = INQ_HIS;
			send(socketfd, msg, sizeof(MSG),0);
			inq_his(socketfd,msg);
*/			break;
		case 5:
			//退出
			msg->flags[0] = QUIT;
			send(socketfd, msg, sizeof(MSG),0);
			return;
			break;
		default:
			printf("输入错误！\n");
			break;
		}
	}
}


