#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "register.h"
#include "book_management.h"
#include "interface.h"

void load_loan(FILE *file)
{
	
	
	file = fopen("loan.txt", "r");
	
	 //Book头指针
	Book * thisbook;
	while(1)
	{
		Register * p = L->next;
		Book * h = H->next;
		int isF = 0;
		Book * thisbook;
		int xid;
		char * user1 = (char *)malloc(sizeof(char)*99);
		if(feof(file))
		{
			break;
		}
		
		
		fscanf(file, "%[^\t]%*c\t%d\n", user1, &xid);
		//printf("\n%s\n", user1);
		while(h)
		{
			
			if(h->id == xid)
			{
			
				thisbook = h;
				break;
			}
			h=h->next;
		}
		while(p)
		{
			//char * user1 = (char *)malloc(sizeof(char)*99);
			if(strcmp(user1,p->username)==0)
			{
				Book * find_this = p->hasborrow; //指向找到的用户的hasborrowed，指向头指针 
				while(1)
				{
					
					if(find_this->next == NULL)
					{
						Book * ad = (Book *)malloc(sizeof(Book));
						//printf("\nthisbook id:%d\n", thisbook->id);
						ad->id = thisbook->id;
						ad->title = thisbook->title;
						ad->author = thisbook->author;
						ad->year = thisbook->year;
						ad->copies = thisbook->copies;
						find_this->next = ad;
						ad->next = NULL;
						isF = 1;
						break;					
					}
					
					find_this = find_this->next;	
				}
				if(isF == 1)
				{
					break;
				}
			}
			p=p->next;
			
		}
	}
}

void Login_menu()
{
	int i;
	char * logname = (char *)malloc(sizeof(char)*99);
	char * logword = (char *)malloc(sizeof(char)*99);
	
	
	printf("Please enter your username: ");
	getchar();
	scanf("%[^\n]", logname);
	scanf("%*[^\n]%*c");
	printf("Please enter yout password: ");
	getchar();
	scanf("%[^\n]", logword);
	scanf("%*[^\n]%*c");
	//getchar();
	char lib[] = "librarian";
	if(strcmp(lib, logname) == 0)
	{
		management();
	}
	
	i = match(logname, logword);
	if(i == 1)
	{
		printf("Login successfully\n");
		// 开始用户操作界面 
		service_menu(logname);
	}
	else
	{
		if(i == 0)
		{
			printf("\nwrong password. Please try again: ");
			Login_menu();
		}
		if(i== -1)
		{
			printf("\nNo such username.\n");
			Login_menu();
		}
	}
	
}
//匹配账号 
int match(char * username, char * logword)
{
	Register * h = L->next;
	char * u = username;
	char * l = logword;
//	printf("%s\n", username);
//	printf("%s\n", logword);
	while(h != NULL)
	{
		//printf("u--%s\n",h->username);
		//printf("p--%s\n",h->password);
		if(strcmp(u, h->username) == 0)
		{
			if(strcmp(l, h->password) == 0)
			{
				return 1;
			}
			else
			{
				//printf("\nwrong password. Please try again: ")
				return 0;
			}
		}
		h = h->next;	
	}	
	
	return -1;//printf("\nNo such username.");
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void service_menu(char * _username)
{
	Register * p = L->next;
	Register * nowLog;
	while(p)//通过username在链表中寻找用户账号 
	{
		if(strcmp(_username, p->username) == 0)
		{
			nowLog = p;   //nowlog 指向寻找到的用户 
		}
		p = p->next;
	}
	printf("\nusername: %s\n", nowLog->username);
	
	int chose = 5;
	do{
		char * answer = (char*)malloc(sizeof(char)*10);
		printf("\nLog in as: %s\n", _username);
		printf("1) Borrow a book\n");
		printf("2) Return a book\n");
		printf("3) Search for books\n");
		printf("4) Display all books\n");
		printf("5) Log out\n");
		printf("  Option: ");
		getchar();
		scanf("%s", answer);
		scanf("%*[^\n]%*c");
		chose = atoi(answer);
		free(answer);
		
		switch(chose)
		{
			case 1:
				borrow_log(nowLog);
				break;
			case 2:
				return_log(nowLog);
				break;
			case 3:
				searchbook();
				break;
			case 4:
				Out(H);
				break;
			case 5:
				//main_menu();
				break;
			default:
				printf("Please try again: \n");
		}
	}while(chose != 5);
	store_user("user.txt");
}

void borrow_log(Register * nowlog)
{
	int id;
	Book * p = H->next;
	Book * q;
	printf("\nEnter the ID of the book you wish to borrow:");
	//getchar();
	scanf("%d", &id);
	scanf("%*[^\n]%");
	int flag = 1;
	//
	while(p)
	{
		if(id == p->id) //找到了那个id的书， p指向这个书 
		{
			if(p->copies == 0)
			{
				printf("\nThere is no book left.");
				break;
			}
			else
			{
				flag = borrowlink(nowlog, id, p);
				if(flag == 0)
				{
					printf("\nYou have successfully borrowed the book!");
					p->copies--;
					break;
				}
				else
				{
					printf("\nYou have already borrowed this book\n");
					borrow_log(nowlog);
					break;
				}	
			}
			
		}
		p=p->next;
	}
	if(p == NULL)
	{
		printf("\nThere is no such book.");
	}
}

int borrowlink(Register * log, int bookid, Book * b) //b指向那本书的位置 
{
	
	
	int bkid;
	
	Register * nowlog = log;
	Book * h = nowlog->hasborrow;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	
	//printf("%s\n", nowlog->username);
	//printf("add\n");
	//printf("\n");
	//printf("%d", b->id);
	b->isborrow = 1;
	while(h->next != NULL)
	{
		h=h->next;
		if(h->id == bookid)
		{
			
			return 1;
		}
	}
	
	while(1)
	{
		
		//printf("\n----\n");
		if(h->next == NULL)
		{
			Book * book = (Book *)malloc(sizeof(Book));  //创建书的结点 
	
			book->id = b->id;
			book->title = b->title;
			book->author = b->author;
			book->year = b->year;
			book->copies = b->copies;
			
				
			h->next = book;
			book->next = NULL;
			break;
		}
		
		h=h->next;
	}
	Register *p=L->next;
	Book *a=p->hasborrow->next;
	FILE *file = fopen("loan.txt","a+");
	//fprintf(file, "%s\t%s\n","Username","loan");
	fprintf(file, "%s\t%d\n", nowlog->username, bookid);
	
	fclose(file);
		
	//store_user("user.txt");
	return 0;
}

int return_log(Register * nowlog)
{
	int id;
	Book * p = H->next;
	Book * q;
	if(nowlog->hasborrow->next == NULL)
	{
		printf("\nYou have returned all books\n");
		return;
	}
	Out(nowlog->hasborrow);
	printf("\nEnter the ID of the book you wish to return：");
	scanf("%d", &id);
	
	while(p)
	{
		if(id == p->id) //找到了那个id的书， p指向这个书 
		{
			//printf("find");
			returnlink(nowlog, id, p);
			p->copies++;
			printf("\nYou have successfully return the book!\n");
			
			break;			
		}
		p=p->next;
	}
	if(p == NULL)
	{
		printf("\nThere is no such book.\n");
	}
	//store_user("user.txt");
}

void returnlink(Register * n, int i, Book * b)
{
	Book *p; 
	Book *pr = n->hasborrow; //指向头结点 
	//Out(pr);
	b->isborrow = 0;
	while(pr->next != NULL)
	{
		//printf("prepare delete");
		p = pr->next;
		//printf("%d", p->id);
		if(p->id == i)
		{
							
			pr->next = p->next;
			free((void *)p);
			break;
		}
		
		pr = pr->next;	
	} 
	
	
	Register * x;
	Book *a;
	FILE *file = fopen("loan.txt","w+");
	//fprintf(file, "%s\t%s\n","Username","loan");
	for(x=L->next ; x!=NULL ; x=x->next)
	{
		for(a=x->hasborrow->next ; a!=NULL ; a=a->next)
		{
			
			printf("id:\n%d\n", a->id);
			fprintf(file, "%s\t%d\n", x->username, a->id);
		}
	}
	fclose(file);
//	while(x)
//	{
//		Book *a = x->hasborrow->next;
//		while(a != NULL)
//		{
//			printf("id:\n%d\n", a->id);
//			
//			fprintf(file,"%s\t%d\n", x->username, a->id);
//			a=a->next;
//		}
//		x=x->next;
//	}
	//fprintf(file, "%s\t%d\n", nowlog->username, bookid);
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/*
int main()
{
	
	Register * a, *b;
	
	Create("book.txt");
	
	
	load_user("user.txt");
	mainMenu();
	int choose;
	scanf("%d", &choose);
	switch(choose)
	{
		case 1:
			adduser();
			break;
		case 2:
			Login_menu();
			break;
		case 3:
			//searchbook();
			printf("search\n");
			break;
		case 4:
			//Out(H);
			printf("show\n");
			break;
		default:
			printf("Please enter a valid choose:");		
	}
	output();
	store_user("user.txt");
	
}
*/
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


int load_user(FILE * file)
{
	int i;
	if(file == NULL)
	{
		printf("Can't open");
		exit(EXIT_FAILURE);
	}
	Register *p,*last;
	CreateRegister(L);
	last = L;
	
	file = fopen("user.txt", "r");
	fscanf(file , "%*[^\n]");
	while(1)
	{
		if(feof(file))
		{
			break;
		}
		CreateRegister(p);
		p->username = (char *)malloc(sizeof(char)*100);
		p->password = (char *)malloc(sizeof(char)*100);
		fscanf(file, "%s\t%s\n", p->username, p->password);
		p->hasborrow = (Book *)malloc(sizeof(Book));
		p->hasborrow->next = NULL; 
		last->next = p;
		last = p;
	}
	last->next = NULL;
	fclose(file);
}

int store_user(FILE *file)
{
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
} 

/***
void load_loan(FILE *file)
{
	int i;
	if(file == NULL)
	{
		printf("Can't open");
		exit(EXIT_FAILURE);
	}
	Register *p,*last;
	//CreateRegister(L);
	//last = L;
	
	file = fopen("loan.txt", "r");
	//fscanf(file , "%*[^\n]");
	while(1)
	{
		if(feof(file))
		{
			break;
		}
		fscanf(file, "%s\t%d\n", p->username, p->password);
		
		
	}
	last->next = NULL;
	fclose(file);	
}


void store_loan(FILE *file)
{
	if((file = fopen("loan.txt", "r"))==NULL)
	{
		file = fopen("loan.txt", "w");
		fclose(file);
	}
	
	Register *p = L->next;
	file=fopen("loan.txt", "w");
	while(p)
	{
		fprintf(file, "%s\t%d\n",p->username,);
		p=p->next;
	}
	fclose(file);
 } 
***/
//添加用户 
void adduser()
{
	int number = 0;
	Register * p = L, *s;
	char * name = (char *)malloc(sizeof(char)*99);
	char * word = (char *)malloc(sizeof(char)*99);
	
	do{
		printf("Please enter a username: ");
		getchar();
		scanf("%[^\n]", name);
		scanf("%*[^\n]%*c");
		printf("Please enter a password: ");
		getchar();
		scanf("%[^\n]", word);
		scanf("%*[^\n]%*c");
	}while(check(name) == 0);
	
	
	
	while(1)
	{
		if(p->next == NULL)
		{
			CreateRegister(s);
			s->username = name;
			s->password = word;
			s->hasborrow = (Book *)malloc(sizeof(Book));
			s->hasborrow->next = NULL;
			p->next = s;
			s->next = NULL;
			break;
		}
		p=p->next;
	}
	store_user("user.txt");
	printf("\nRegistered library account successfully!\n");
}
//判断用户是否已在
int check(char * username)
{
	//printf("\ncheck: %s", username);
	Register * p;
	char manager[] = "librarian";
	for(p = L->next; p!=NULL ; p=p->next)
	{
		if(strcmp(p->username, username) == 0 || strcmp(username, manager)==0)
		{
			printf("\nSorry, Registration unsuccessfully. The username you entered already exists.\n\n");
			return 0;
		}
	 }
	return 1; 
} 

//输出链表 
void output()
{
	Register *p = L->next, q;
	while(1)
	{
		printf("%s\n", p->username);
		printf("%s\n", p->password);
		
		if(p->next == NULL)
		{
			break;
		}
		p=p->next;
	}
}

void log_Menu()
{
	printf("Please choose an option: \n");
	printf("1) Borrow a book\n");
	printf("2) Return a book\n");
	printf("3) Search for books\n");
	printf("4) Display all books\n");
	printf("5) Log out\n");
	printf("    option: \n");
	printf("\n");
}


