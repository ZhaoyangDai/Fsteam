#include "server.h"

/******************************
 * 注册
 * ***************************/
int usr_register(int newfd,data_t *usrMsg,sqlite3*db)
{
	int ret = -1;
	char sql[300];
	char * errmsg;

	/*添加用户名、密码到用户数据表中*/
	sprintf(sql,"insert into usr_data values('%s','%s');",\
			usrMsg->usrname,usrMsg->usrpsw);
	/*验证用户名是否存在*/
	if(sqlite3_exec(db,sql,NULL,NULL,&errmsg) != SQLITE_OK)
	{
		printf("%s\n",errmsg);
		strcpy(usrMsg->info.warn,"user is exist.");
	}else{
		printf("client register success.");
		strcpy(usrMsg->info.warn,"register success.");
	}
	usrMsg->info.retcli = 1;
	send(newfd,&usrMsg,sizeof(data_t),0);
	return 0;
}

/******************************
 * 登录
 * ***************************/
int usr_login(int newfd,data_t *usrMsg,sqlite3 *db)
{
	char sql[300];
	char *errmsg;

	/*查找用户名和查找密码*/
	sprintf(sql,"select * from usr_data where usrname='%s',usrpsw=%s;",\
			usrMsg->usrname,usrMsg->usrpsw);
	if(sqlite3_exec(db,sql,NULL,NULL,&errmsg) != SQLITE_OK)
	{
		printf("%s\n",errmsg);
		strcpy(usrMsg->info.warn,"user is no find.");
	}else{
		printf("execute successfully!");
		strcpy(usrMsg->info.warn,"longin success.");
	}
	usrMsg->info.retcli = 1;
	send(newfd,&usrMsg,sizeof(data_t),0);
	return 0;
}

/******************************
 * 忘记密码/修改账户密码
 * ***************************/
int usr_change(int newfd,data_t *usrMsg,sqlite3 *db)
{
	char sql[300] = {};
	char *errmsg;

	sprintf(sql,"update usr_data  set usrpsw='%s' where usrname='%s';",\
			usrMsg->usrpsw,usrMsg->usrname);
	if(sqlite3_exec(db,sql,NULL,NULL,&errmsg) != SQLITE_OK)
	{
		printf("%s\n",errmsg);
		strcpy(usrMsg->info.warn,"password changed fail.");
	}else{
		printf("execute successfully!");
		strcpy(usrMsg->info.warn,"password changed success.");
	}
	usrMsg->info.retcli = 1;
	send(newfd,&usrMsg,sizeof(data_t),0);
	return 0;
}

/*****************************
 * 查看操作历史记录
 * ***************************/
int usr_sistory(int newfd,data_t *usrMsg,sqlite3 *db)
{
	char sql[300] = {};
	char *errmsg;

	sprintf(sql,"select * from record where name='%s'",\
			usrMsg->history);
	if(sqlite3_exec(db,sql,history_callback,\
				(void *)&newfd,&errmsg) != SQLITE_OK)
	{
		printf("%s\n",errmsg);
		strcpy(usrMsg->info.warn,"get sistory error.");
	}else{
		printf("execute successfully!");
		strcpy(usrMsg->info.warn,"get history success.");
	}
	usrMsg->history[0] = '\0';
	usrMsg->info.retcli = 1;
	send(newfd,usrMsg,sizeof(data_t),0);
	return 0;
}

/*****************************
 *历史查询回调函数
 ****************************/
int history_callback(void *arg,int f_num,char**f_value,char**f_name)
{
	data_t msg;
	int newfd;

	newfd = *((int *)arg);
	sprintf(msg.history,"%s,%s",f_value[1],f_value[2]);
	send(newfd,&msg,sizeof(data_t),0);
	return 0;
}
