#include "interface.h"

#include "register.h"
#include "book_management.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void mainMenu()
{
	//int option;
	printf("Please choose an option:\n");
	printf("1) Register an account.\n");
	printf("2) Login.\n");
	printf("3) Search for books.\n");
	printf("4) Display all books.\n");
	printf("5) Quit.\n");
	printf("  Option: ");
}

void get_only_oneword()
{
	while(getchar() != '\n')
	{
		continue;
	}
}


void main_menu()
{

	int choice = 5;
	
	do{
		char * answer = (char*)malloc(sizeof(char)*10);
		mainMenu();
		//getchar();
		scanf("%s", answer);
		scanf("%[^\n]%*c");
		choice = atoi(answer);
		free(answer);
		//scanf("%c", &answer);
		//answer = getchar();
		

		
		switch(choice)
		{
			case 1:
				adduser();
				//output();
				break;
			case 2:
				//output();
				Login_menu();
				break;
			case 3:
				searchbook();
				break;
			case 4:
				Out(H);
				break;
			case 5:
				printf("Goodbye");
				exit(0);
				//return;
				break;
			default:
				printf("\nSorry, the option you entered was invalid, please try again\n\n");
		}
		//fflush();
		//getchar(); 
	}while (choice != 5 );
	//store("book.txt");
	return;
}

void run_interface()
{	
	system("color 3E");
	load_books("book.txt");
	//Out(H);
	
	load_user("user.txt");
	//output();
	main_menu();
	
	return;
}
