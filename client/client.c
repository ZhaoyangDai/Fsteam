#include "client.h"

/*************************************************
Function: 		client 				// 函数名称
Description:  	主函数				// 函数功能、性能等的描述
Calls: 			register_func,login_func 	// 被本函数调用的函数清单
Called By: 							// 调用本函数的函数清单
Input: 				 				// 输入参数说明
Output: 		socketfd,msg		// 对输出参数的说明
Return: 							// 函数返回值的说明
Others: 							// 其它说明
*************************************************/
int main(int argc, const char *argv[])
{

	//初始化套接字
	net_init(argv);

	while(1)
	{
		int n;
		printf("员工管理系统\n");
		printf("*****************\n");                                          
		printf("*1. 注册        *\n");
		printf("*2. 登录        *\n");
		printf("*3. 忘记密码    *\n");
		printf("*4. 退出        *\n");
		printf("*****************\n");
		printf("请选择：\n");
		//获得选择
		scanf("%d",&n);
		getchar();

		switch(n){
		case 1:
			//发送"注册"
			msg.flags[0] = REGISTER;
			send(socketfd, &msg, sizeof(MSG),0);
			//注册函数
			register_func(socketfd, &msg);
			break;
		case 2:
			//发送"登录"
			msg.flags[0] = LOGIN;
			send(socketfd, &msg, sizeof(MSG),0);
			//登录函数
			login_func(socketfd, &msg);
			break;
		case 3:
			//发送"忘记密码"
			msg.flags[0] = FIND;
			send(socketfd, &msg, sizeof(MSG),0);
			find_psw(socketfd, &msg);
			break;
		case 4:
			//发送"退出"
			msg.flags[0] = QUIT;
			send(socketfd, &msg, sizeof(MSG),0);
			//关闭套接字
			close(socketfd);
			return 0;
		default:
			printf("输入错误！");
			break;
		}

	}


	return 0;
}

