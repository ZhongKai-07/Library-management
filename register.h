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

