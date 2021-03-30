#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "book_management.h"
#define CreateRegister(p) p=(Register *)malloc(sizeof(Register));



typedef struct Register
{
	char * username;
	char * password;
	Book * hasborrow; //
	struct Register * next;
}Register;

Register * L; //指向头节点 

Register * linklist(); //创建链表以及写入管理员账号 
void adduser(); //注册用户 
int check(char * ); //检查是否已注册 
void output(); //打印链表 
int store_user(FILE *file);
int load_user(FILE * file);
void mianMenu();

void Login_menu();
int match(char * username, char * logword);
void service_menu(char * _username);
void borrow_log(Register * nowlog);
int borrowlink(Register * log, int bookid, Book * b);

void load_loan(FILE *file);
void store_loan(FILE *file);

/***
	if((file = fopen("user.txt", "r"))==NULL)
	{
		file = fopen("user.txt", "w");
		fclose(file);
	}
	
	Register *p = L->next;
	file = fopen("user.txt", "w");
	fprintf(file, "%s\t%s\t%s\n", "Username", "Password","loan");
	while(p)
	{
		fprintf(file, "%s\t%s\n", p->username, p->password);
//		while(p->hasborrow->next != NULL)
//		{
//			fprintf(file,"\t%d",p->hasborrow->next->id);
//		}
		//fprintf(file, "\n");
		p=p->next;
	}
	fclose(file);

//////
***/
