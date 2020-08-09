#include "server.h"

/*****************************
 *查看员工信息
 ****************************/
int emp_cat(int newfd,empinfo_t *empMsg,sqlite3 *db)
{
	char sql[300] = {};
	char *errmsg;

	sprintf(sql,"select * from emp_info where name='%s';",empMsg->name);
	if(sqlite3_exec(db,sql,NULL,NULL,&errmsg) != SQLITE_OK)
	{
		printf("%s\n",errmsg);
		strcpy(empMsg->warn,"get message error.");
	}else{
		printf("execute successfully!");
	}
	return 0;
}

/*****************************
 *更新员工信息
 ****************************/
int emp_update(int newfd,empinfo_t *empMsg,sqlite3 *db)
{
	char sql[300] = {};
	char *errmsg;

	sprintf(sql,"update emp_info set %s='%s' where name='%s';",\
			empMsg->tag,empMsg->newdata,empMsg->name);
	if(sqlite3_exec(db,sql,NULL,NULL,&errmsg) != SQLITE_OK)
	{
		printf("%s\n",errmsg);
		strcpy(empMsg->warn,"message update error.");
	}else{
		printf("execute successfully!");
	}
	return 0;
}

/*****************************
 *添加员工
 ****************************/
int emp_add(int newfd,empinfo_t *empMsg,sqlite3 *db)
{
	char sql[300] = {};
	char *errmsg;

	sprintf(sql,"insert into emp_info VALUES('%s','%s',%d,%d,%.2f,'%s','%s','%s','%s','%s');",\
			empMsg->name,empMsg->sex,empMsg->age,empMsg->year,\
			empMsg->salary,empMsg->department,empMsg->telephone,\
			empMsg->E_mail,empMsg->address,empMsg->history);
	if(sqlite3_exec(db,sql,NULL,NULL,&errmsg) != SQLITE_OK)
	{
		printf("%s\n",errmsg);
		strcpy(empMsg->warn,"employee is already exists.");
	}else{
		printf("execute successfully!");
	}
	return 0;
}

/*****************************
 *删除员工
 ****************************/
int emp_remove(int newfd,empinfo_t *empMsg,sqlite3 *db)
{
	char sql[300] = {};
	char *errmsg;

	sprintf(sql,"delete from emp_info where usrname='%s';",empMsg->name);
	if(sqlite3_exec(db,sql,NULL,NULL,&errmsg) != SQLITE_OK)
	{
		printf("%s\n",errmsg);
		strcpy(empMsg->warn,"employee removed fail.");
	}else{
		printf("execute successfully!");
	}
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
