#include "server.h"

/*****************************
 *查看员工信息
 ****************************/
int emp_cat(int newfd,empinfo_t *empMsg,sqlite3 *db)
{
	char sql[300] = {};
	char *errmsg;

	sprintf(sql,"select * from emp_info where name='%s';",empMsg->name);
	if(sqlite3_get_table(db,sql,&restp,&nrow,&ncloumn,&errmsg) != SQLITE_OK)
	{
		printf("%s\n",errmsg);
		strcpy(empMsg->warn,"get message error.");
	}else{
		printf("execute successfully!");
		strcpy(empMsg->warn,"employee cat success.");
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
		strcpy(empMsg->warn,"employee update success.");
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
		strcpy(empMsg->warn,"employee insert success.");
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
		strcpy(empMsg->warn,"employee delete success.");
	}
	return 0;
}


