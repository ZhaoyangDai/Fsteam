#include "server.h"

/*********************************************************
 * Function Name  : usr_register
 * Description    : if user not exist,register success
 * Input          : accept socket , MSG 
 * Output         : None
 * Return         : None
 * *******************************************************/
void usr_register(int newfd,MSG *usrMsg)
{
	int ret = -1;
	char sql[300] = {0};

	memset(usrMsg,0,sizeof(MSG));
	recv(newfd,usrMsg,sizeof(MSG),0);

	/*验证用户是否存在*/
	sprintf(sql,"select * from usr_data where username='%s' and passwd='%s' and type=%d;",\
			usrMsg->username,usrMsg->passwd,*usrMsg->type);
	if(sqlite3_get_table(db,sql,&resultp,&nrow,&ncloumn,&errmsg) != SQLITE_OK)
	{
		printf("%s\n",errmsg);
	}else{
		printf("user data search over...\n");
	}

	if(nrow >= 1)
	{
		send(newfd,usrMsg,sizeof(MSG),0);
		printf("user is already exist!\n");		
	}
	if(nrow == 0)
	{
		printf("user can register...\n");

		/*添加用户名、密码到用户数据表中*/
		sprintf(sql,"insert into usr_data values(null,'%s','%s',%d);",\
				usrMsg->username,usrMsg->passwd,usrMsg->type[0]);

		if(sqlite3_exec(db,sql,NULL,NULL,&errmsg) != SQLITE_OK)
		{
			printf("%s\n",errmsg);
		}else{
			printf("===== user register success =====\n");

			/*查找用户id*/
			sprintf(sql,"select id from usr_data where username='%s' and passwd='%s' and type=%d;",\
					usrMsg->username,usrMsg->passwd,*usrMsg->type);
			if(sqlite3_get_table(db,sql,&resultp,&nrow,&ncloumn,&errmsg) != SQLITE_OK)
			{
				printf("%s\n",errmsg);
			}else{
				if(nrow == 0){
					usrMsg->flags[0] = ERROR;
					send(newfd,usrMsg,sizeof(MSG),0);

				}else{
					usrMsg->id = atoi(resultp[1]);
					printf(">>>your user id is >%d\n",usrMsg->id);

					/*添加员工信息*/
					sprintf(sql,"insert into emp_data values(%d,'%s',%d,'%s','%s','%s');",\
							usrMsg->id,usrMsg->name,usrMsg->age,usrMsg->sex,usrMsg->phone,usrMsg->addr);
					if(sqlite3_exec(db,sql,NULL,NULL,&errmsg) != SQLITE_OK)
					{
						printf("%s\n",errmsg);
						usrMsg->flags[0] = ERROR;
						send(newfd,usrMsg,sizeof(MSG),0);
					}else{
						printf("===== employee message insert success.=====\n");
						usrMsg->flags[0] = REG_SUC;
						send(newfd,usrMsg,sizeof(MSG),0);
					}
				}
			}
		}
	}
}

/*********************************************************
 * Function Name  : user_login
 * Description    : if the user is exist,login success
 * Input          : fmtaccept socket , MSG 
 * Output         : None
 * Return         : None
 * *******************************************************/
void usr_login(int newfd,MSG *usrMsg)
{
	int ret = -1;
	char sql[300];

	recv(newfd,usrMsg,sizeof(MSG),0);

	/*验证用户是否存在*/
	sprintf(sql,"select * from usr_data where username='%s' and passwd='%s';",\
			usrMsg->username,usrMsg->passwd);
	if(sqlite3_get_table(db,sql,&resultp,&nrow,&ncloumn,&errmsg) != SQLITE_OK)
	{
		printf("%s\n",errmsg);
	}else{
		printf("user message search over...\n");
	}
	/*将权限信息发送给客户端*/
	is_root(usrMsg);

	if(nrow >= 1)
	{
		usrMsg->flags[0] = LOGIN_SUC;
		send(newfd,usrMsg,sizeof(MSG),0);
		printf("++++++++++++++++++++++++++++++\n");
		printf("===== usr login success.=====\n");
		printf("++++++++++++++++++++++++++++++\n");
		login_win(newfd,usrMsg);
	}
	if(nrow == 0)
	{
		send(newfd,usrMsg,sizeof(MSG),0);
		printf("user/password wrong!\n");
	}
}

/*********************************************************
 * Function Name  : passwd_find
 * Description    : base on username and id to update password
 * Input          : fmtaccept socket , MSG 
 * Output         : None
 * Return         : None
 * *******************************************************/
void passwd_find(int newfd,MSG *usrMsg)
{
	int ret = -1;
	char sql[300] = {};

	recv(newfd,usrMsg,sizeof(MSG),0);

	sprintf(sql,"select * from usr_data where username='%s' and id=%d;",\
			usrMsg->username,usrMsg->id);
	if(sqlite3_get_table(db,sql,&resultp,&nrow,&ncloumn,&errmsg) != SQLITE_OK)
	{
		printf("%s\n",errmsg);
	}else{
		printf("user data search over...\n");
	}

	if(nrow >= 1)
	{
		usrMsg->flags[0] = CHECK_OK;
		/*将帐号存在结果发送给客户端*/
		send(newfd,usrMsg,sizeof(MSG),0);
		recv(newfd,usrMsg,sizeof(MSG),0);

		sprintf(sql,"update usr_data set passwd='%s' where  id=%d;",\
				usrMsg->passwd,usrMsg->id);
		if(sqlite3_exec(db,sql,NULL,NULL,&errmsg) != SQLITE_OK)
		{
			printf("%s\n",errmsg);
			usrMsg->flags[0] = ERROR;
			send(newfd,usrMsg,sizeof(MSG),0);
		}else{
			printf("===== password update success.=====\n");
			usrMsg->flags[0] = CGE_SUC;
			send(newfd,usrMsg,sizeof(MSG),0);
		}
	}
	if(nrow == 0)
	{
		printf("user is noe exist!\n");
		usrMsg->flags[0] = ERROR;
		ret = send(newfd,usrMsg,sizeof(MSG),0);
	}
}

/*********************************************************
 * Function Name  : login_win
 * Description    : if user login success,can do another
 * Input          : fmtaccept socket , MSG 
 * Output         : None
 * Return         : None
 * *******************************************************/
void login_win(int newfd,MSG * usrMsg)
{
	while(1){

		recv(newfd,usrMsg,sizeof(MSG),0);

		switch(usrMsg->flags[0])
		{
		case REGISTER:
			usr_register(newfd,usrMsg); /*添加员工信息*/
			break;
		case DELE_USER:
			emp_remove(newfd,usrMsg); /*删除员工信息*/
			break;
		case INQ_INFO:
			emp_cat(newfd,usrMsg); /*查看员工信息*/
			break;
		case CGE_USER:
			emp_data_update(newfd,usrMsg); /*更新员工信息*/
			break;
		case CGE_SUC:
			passwd_change(newfd,usrMsg); /*修改密码*/
			break;
		case QUIT:
			printf("back menu...\n");
			return;
			break;
		default:
			printf("make choice error!\n");
			return;
			break;
		}
	}
	return;
}

/*********************************************************
 * Function Name  : is_root
 * Description    : Identify user's permissions
 * Input          : fmtaccept socket , MSG 
 * Output         : None
 * Return         : None
 * *******************************************************/
void is_root(MSG *usrMsg)
{
	int ret = -1;
	ret = strcmp("root",usrMsg->username);
	if(ret == 0){
		usrMsg->type[0] = 0;
	}else{
		usrMsg->type[0] = 1;
	}
}

