#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book_management.h" 
//#include "register.h"
#define CreateNode(p) p=(Book *)malloc(sizeof(Book));
#define DeleteNode(p) p=free((void *)p);

Book * H;//指向头结点 ··· 
int load_books(FILE * file)
{
	Book * h, *p, *last;
	CreateNode(H);
	last = H;
	
	file = fopen("book.txt","r");
	int i;
	if(file == NULL)
	{
		printf("Can't Open");
		exit(EXIT_FAILURE);
	}
	//printf("CreateNode:\n");
	fscanf(file, "%*[^\n]");
	while(1)
	{
		if(feof(file))
		{
			break;
		}
		CreateNode(p);
		p->title = (char *)malloc(sizeof(char)*100);
		p->author = (char *)malloc(sizeof(char)*100);
		fscanf(file, "%d\t%[^\t]%*c\t%[^\t]%*c\t%d\t%d\n",   &p->id , p->title, p->author, &p->year, &p->copies);
		p->isborrow = 0;
		last->next = p;
		last = p;
	}
	last->next = NULL;
	//printf("endnode");
	fclose(file);
	//return h;	
}

int store_books(FILE *file)
{
	
	if((file = fopen("book.txt", "r"))==NULL)
	{
		file = fopen("book.txt", "w");
		fclose(file);
	}
	
	Book *p = H->next;
	file = fopen("book.txt", "w");
	fprintf(file, "%s\t%s\t%s\t%s\t%s\n", "ID", "title", "authors", "year", "copies"); 
	while(p)
	
	{
		fprintf(file, "%d\t%s\t%s\t%d\t%d\n", p->id, p->title, p->author, p->year, p->copies);
		p = p->next;
	}
	fclose(file);
	//return;
}


void Out(Book * book)
{
	Book *p = book->next, q;
	//printf("%s\n", p->title);
	//printf("\nout------\n");
	printf("%s\t%-40s\t%-40s\t%-10s\t%-4s\n", "id", "title", "authors", "year", "copies"); 
	while(1)
	{
		printf("%d\t%-40s\t%-40s\t%-10d\t%-4d\n", p->id ,p->title,p->author,p->year ,p->copies);
		if(p->next == NULL)
		{
			break;
		}
		p = p->next; 
	}
}
///创建新结构加入 
Book creat_book()
{
	Book newbook;
	char * titlen = (char *) malloc (sizeof(char)*99);
	char * authorsn = (char *)malloc(sizeof(char)*99);	
	char * yearn = (char *)malloc(sizeof(char)*10);
	int  copiesn;
	printf("\nPlease enter the book title: ");
	getchar();
	scanf("%[^\n]%*c", titlen);
	printf("Please enter the author of the book: ");
	scanf("%[^\n]%*c", authorsn);
	printf("Please enter the year of the book: ");
	scanf("%s", yearn);
	printf("Please enter the copies of the book: ");
	getchar();
	scanf("%d", &copiesn);
	//printf("\n");
	if(atoi(authorsn) != 0)
	{
		printf("\nPlease enter a valid author name\n");
		creat_book();
	}
	if(atoi(yearn) == 0)
	{
		printf("\nPlease enter a valid year\n");
		creat_book();
	}
	newbook.title = titlen;
	newbook.author = authorsn;
	newbook.year = atoi(yearn);
	newbook.copies = copiesn;
	
	return newbook;
}

//加入书目 
int add_book(Book book)
{
	Book *p = H, *s;  //p是链表头指针 
	int length = 1;

	while(1)
	{
		length += 1;
		p=p->next;
		if(p->next == NULL)
		{
			CreateNode(s);
			s->id = length;
			s->title = book.title;
			s->author = book.author;
			s->year = book.year;
			s->copies = book.copies;
			
			p->next = s;
			s->next = NULL;
			
			printf("\nBook was successfully added.\n");
			return 0;
		}
	}
}
/*
Book find_remove()  
{
	Book newbook;
	int idnum;
	Book * p;
	printf("\nPlease enter the id of the book you wish to remove.\n");
	scanf("%d", &idnum);
	
}
*/
int remove_book()
{
	Book *pr = H, *p;  //p是链表头指针 
	int length = 1;
	int idnum;
	printf("\nPlease enter the id you want to remove:");
	scanf("%d", &idnum);
	while(pr->next)
	{
		length += 1;
		p=pr->next;
		
		if(p->id == idnum )
		{
			if(p->isborrow == 0)
			{
				pr->next = p->next;
				free((void*)p);				
			}
			else
			{
				printf("\nThis book has been borrowed\n");
				printf("Please try again\n");
				remove_book();
				break;
			}

		}
		pr=pr->next;
	}		
}

void searchbook()
{
	int option ;
	//Book * p = H;
	BookArray findtitle;
	BookArray findauthor;
	BookArray findyear;
	printf("Please choos an option:\n");
	printf("1) Find books by title\n");
	printf("2) Find boos by author\n");
	printf("3) Find book by year\n");
	printf("4) Return to previous menu\n");
	printf("Option: ");
	scanf("%d", &option);
	scanf("%[^\n]%*c");
	
	char * stitle = (char *)malloc((sizeof(char)*99)); 
	
	int syear;
	switch(option)
	{
		case 1:
		{
			printf("Please enter the title: ");
			getchar();
			scanf("%[^\n]", stitle);
			findtitle = find_book_by_title(stitle);
			if (findtitle.array->next == NULL)
			{
				printf("\nThere has no such book\n");
				break;
			}
			else
			{
				Out(findtitle.array);
				break;
			}
			
		}
		case 2:
		{	
			char * sauthor = (char *)malloc((sizeof(char)*20));
			printf("Please enter the author: ");
			getchar();
			scanf("%[^\n]%*c", sauthor);
			if(atoi(sauthor) != 0)
			{
				printf("\nPlease enter a valid author name\n");
				searchbook();
			}

			findauthor = find_book_by_author(sauthor);
			find_book_by_author(sauthor);
			Out(findauthor.array);
			free((void*) sauthor);
			break;
		}
		case 3:
			//printf("Please enter the year\n");
			printf("Please enter the year: ");
			getchar();
			scanf("%d", &syear);
			if(atoi(syear) == 0)
			{
				printf("\nPlease enter a valid year\n");
				searchbook();
			}
			findyear = find_book_by_year(syear);
			Out(findyear.array);
			break;
		case 4:
			printf("back");
			break;
		default:
			printf("Enter again\n");
	}
	free((void*) stitle);
	
 } 

BookArray find_book_by_title(const char * title)
{
	BookArray B={
		(Book *)malloc(sizeof(Book)),
		0
	};
	
	Book *temp; //中间变量 
	Book *pr = H,*last;
	Book *p = H->next;

	last = B.array;
	int count = 0;
	while(p)
	{
		if(strstr(p->title,title) != NULL)
		{
			CreateNode(temp);
			
			temp->id = p->id;
			temp->title = p->title;
			temp->author = p->author;
			temp->year = p->year;
			temp->copies = p->copies;
			
			last->next = temp;
			last = last->next;
		}
		temp = p;
		p = p->next; 
	}
	last->next = NULL;
	B.length = count;
	return B;
}

BookArray find_book_by_author(const char *author)
{
	BookArray a = {
		(Book*)malloc(sizeof(Book)),
		0
	};
	Book* last, * tem;
	last = a.array;
	Book* pr = H;  //链表表头 
	Book* p = H->next;  //第一个数据 
	int count = 0;
	while (p)
	{
		if (strstr(p->author,author) != NULL)
		{
			CreateNode(tem);
			
			tem->title = (char *)malloc(sizeof(char)*99);
			tem->author = (char *)malloc(sizeof(char)*99);
			
			tem->id = p->id;
			tem->title = p->title;
			tem->author = p->author;
			tem->year = p->year;
			tem->copies = p->copies;
			//printf("\ntemp:%d", p->copies);
			last->next = tem;
			last = last->next;
			//count++;
		}
		tem = p;
		p = p->next;
	}
	last->next = NULL;
	a.length = count;
	return a;
}

BookArray find_book_by_year(unsigned int year)
{
	BookArray B={
		(Book *)malloc(sizeof(Book)),
		0
	};
	
	Book *temp; //中间变量 
	Book *pr = H,*last;
	Book *p = H->next;

	last = B.array;
	int count = 0;
	while(p)
	{
		if(year == p->year)
		{
			CreateNode(temp);
			
			temp->id = p->id;
			temp->title = p->title;
			temp->author = p->author;
			temp->year = p->year;
			temp->copies = p->copies;
			
			last->next = temp;
			last = last->next;
			count ++;	
		}
		temp = p;
		p = p->next; 
	}
	last->next = NULL;
	B.length = count;
	return B;

} 
 
void management_menu()
{
	printf("\n\n(Logged in as: librarian)\n");
	printf("Please choose an option: \n");
	printf("1) Add a book\n");
	printf("2) Remove a book\n");
	printf("3) Search for books\n");
	printf("4) Display all books.\n");
	printf("5) Log out\n");
	printf("  option:");
}

void management()
{
	Book newBook;
	int isFlag = 0; //1 yes, 0 again
	int if_add;
	int choose = 5;
	do{
		char * answer = (char*)malloc(sizeof(char)*10);
		management_menu();
		getchar();
		scanf("%s", answer);
		scanf("%*[^\n]%*c");
		choose = atoi(answer);
		free(answer);
		switch(choose)
		{
			case 1:
				newBook = creat_book();
				if_add = add_book(newBook); 
				isFlag = 1;
				Out(H);
				store_books("book.txt");
				break;
			case 2:
				remove_book();
				isFlag = 1;
				break;
			case 3:
				searchbook();
				isFlag = 1;
				break;
			case 4:
				Out(H);
				isFlag = 1;
				break;
			case 5:
				printf("logout\n");
				main_menu();
				isFlag = 1;
				break;
			default:
				printf("Please enter a valid option.\n");
		}
	}while(isFlag == 1);
	//Out(H);
	int ifstore;
	//store("book.txt");
}

