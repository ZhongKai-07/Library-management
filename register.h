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

Register * L; //ָ��ͷ�ڵ� 

Register * linklist(); //���������Լ�д�����Ա�˺� 
void adduser(); //ע���û� 
int check(char * ); //����Ƿ���ע�� 
void output(); //��ӡ���� 
int store_user(FILE *file);
int load_user(FILE * file);
void mianMenu();

void Login_menu();
int match(char * username, char * logword);
void service_menu(char * _username);
void borrow_log(Register * nowlog);
int borrowlink(Register * log, int bookid, Book * b);

