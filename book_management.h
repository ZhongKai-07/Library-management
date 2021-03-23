#ifndef BOOK_MANAGEMENT_GUARD__H 
#define BOOK_MANAGEMENT_GUARD__H

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//#include "register.h"
//#include "book_management.h"

typedef struct node
{
	unsigned int id;
	char * title;
	char  * author;
	unsigned int year;
	unsigned int copies;
	struct node * next;
}Book;

typedef struct _BookArray{
	Book *array;//pointer to linked list 
	unsigned int length;
}BookArray;

Book * H; //指向头节点 

int load_books(FILE *file);

int store_books(FILE *file);
//void showMenu;
void Out(Book * book);

Book creat_book();
int add_book(Book book); 

int remove_book();

void searchbook(); 

BookArray find_book_by_title(const char *title);
BookArray find_book_by_author(const char *author);
BookArray find_book_by_year(unsigned int year);

void management();
#endif
