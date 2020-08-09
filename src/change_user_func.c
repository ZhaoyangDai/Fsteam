#include "client.h"


void add_user_func(DATA *command,int sockfd)
{
	cge_name_func(command,sockfd);
	cge_age_func(command,sockfd);
	cge_sex_func(command,sockfd);
	cge_psw_func(command,sockfd);
	cge_salary_func(command,sockfd);
	cge_dep_func(command,sockfd);
	cge_tele_func(command,sockfd);
	cge_mail_func(command,sockfd);
	cge_addr_func(command,sockfd);
}

void delete_user_func(DATA *command,int sockfd)
{
	printf("没写\n");
}
