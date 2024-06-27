#include <stdio.h>
#include <string.h>
#include "library.h"

void viewUserData(char username[]);
void changePassword(char username[]);
void viewAllBooks();
void searchBook();
void requestBorrow();
void buyBook();
void requestNewBook();
void viewBorrowRequests();

int userMode()
{
	int a=0;
    char username[50],password[50];
    printf("Enter User username: ");
    scanf("%s",username);
    printf("Enter User password: ");
    scanf("%s",password);

    int q = 0;
    for (int i=0;i<listsize(users);i++)
	{
        listentry e;
        retrievelist(i,&e,users);
        if (strcmp(e.user.username,username)==0&&strcmp(e.user.pass,password)==0)
		{
            q=1;
            break;
        }
    }

    if (q) {
        int choice;
        printf("Welcome User\n");
        printf("1. View User Data\n2. Change Password\n3. View All Books\n4. Search Book\n5. Request Borrow\n6. Buy Book\n7. Request New Book\n8. View Borrow Requests\n9. Logout\n");
        scanf("%d",&choice);

        switch (choice)
		{
            case 1:
                viewUserData(username);
                return a;
            case 2:
                changePassword(username);
                return a;
            case 3:
                viewAllBooks();
                return a;
            case 4:
                searchBook();
                return a;
            case 5:
                requestBorrow();
                return a;
            case 6:
                buyBook();
                return a;
            case 7:
                requestNewBook();
                return a;
            case 8:
                viewBorrowRequests();
                return a;
            case 9:
                printf("Logging out...\n");
				a=1;
                return a;
            default:
                printf("Invalid choice.\n");
                return a;
        }
    }
	else
	{
        printf("Invalid username or password.\n");
		return a;
    }
}

void viewUserData(char username[])
{
    printf("User data:\n");
	
	for (int i=0;i<listsize(users);i++)
	{
		listentry e;
		retrievelist(i,&e,users);
		if (strcmp(e.user.username,username)==0)
		{
			printf("Username: %s\nID: %d\nPassword: %s\nNumber of Borrowed Books: %d\n",e.user.username,e.user.id, e.user.pass,e.user.nbor);
			printf("Borrowed Books:\n");
			for (int j=0;j<e.user.nbor;j++)
			{
				printf("  Book %d: %s    Author: %s\n",j+1,e.user.borbk[j].name,e.user.borbk[j].author);
			}
			break;
		}
	}
}

void changePassword(char username[])
{
	char oldPassword[50];
	char newPassword[50];
    printf("Enter your old password: ");
    scanf("%s",oldPassword);
    printf("Enter your new password: ");
    scanf("%s",newPassword);
	
	for (int i=0;i<listsize(users);i++)
	{
        listentry e;
        retrievelist(i,&e,users);
        if (e.user.pass==newPassword)
		{
            printf("Password is already used try again.\n");
            changePassword(username);
        }
    }

    for (int i=0;i<listsize(users);i++)
	{
        listentry e;
        retrievelist(i,&e,users);
        if (strcmp(e.user.username,username)==0&&strcmp(e.user.pass,oldPassword)==0)
		{
            strcpy(e.user.pass,newPassword);
            replacelist(i,e,users);
            saveUsers();
			printf("Password changed successfully.\n");
            return;
        }
    }

    printf("User not found or incorrect password.\n");
}

void viewAllBooks()
{
    printf("Books:\n");
    for (int i=0;i<listsize(books);i++)
	{
        listentry e;
        retrievelist(i,&e,books);
        printf("Title: %s\nAuthor: %s\nnumber: %d\nPrice: %d\n-------------------------------------------------\n",e.book.name,e.book.author,e.book.number,e.book.price);
    }
}

/*void searchBook()
{
    int c;
	char name[50];
	char author[50];
	printf ("1. search by name\n2.search by author");
	scanf("%d",&c);
	
	switch(c)
	{
		case 1:
			printf("Enter Book name to search: ");
			scanf("%s",name);

			for (int i=0;i<listsize(books);i++)
			{
				listentry e;
				retrievelist(i,&e,books);
				if (strcmp(e.book.name,name)==0)
				{
					printf("Name: %s, Author: %s, ID: %d, Number: %d, Price: %.d\n",e.book.name,e.book.author,e.book.number,e.book.price);
					return;
				}
			}
			
			printf("Book not found.\n");
			break;
		case 2:
			printf("Enter Book author to search: ");
			scanf("%s",author);
			
			 int authorFound=0;

			for (int i=0;i<listsize(books);i++)
			{
				listentry e;
				retrievelist(i,&e,books);
				if (strcmp(e.book.author,author)==0)
				{
					printf("Name: %s, Author: %s, ID: %d, Number: %d, Price: %.d$\n-------------------\n",e.book.name,e.book.author,e.book.number,e.book.price);
				    authorFound=1;
				}
			}
			
			if (!authorFound)
			{
				printf("Author not found.\n");
			}
			break;
		default:
			printf("Invalid number selected.\n");
            break;
	}
}*/

void requestBorrow(char username[])
{
	int a=0;
	char name[50];
	listentry x;
	BorrowRequest BR;
	getchar();
	printf ("Enter Book name to borrow: ");
	gets(name);
	
	for (int i=0;i<listsize(books);i++)
	{
		listentry e;
		retrievelist(i,&e,books);
		if (strcmp(e.book.name,name)==0)
		{
			BR.book=e.book;
			a=1;
			break;
		}
	}
			
	if (!a)
	{
		printf("Book not found.\n");
		return;
	}
	
	for (int i=0;i<listsize(users);i++)
	{
		listentry e;
		retrievelist(i,&e,users);
		if (strcmp(e.user.username,username)==0)
		{
			BR.user=e.user;
			break;
		}
	}
	BR.status=0;
	x.BR=BR;
	insertlist (listsize(BRs),x,BRs);
}

void buyBook()
{
	int a=0;
    char name[50];
	getchar();
	printf ("Enter Book name to buy: ");
	gets(name);
	
	for (int i=0;i<listsize(books);i++)
	{
		listentry e;
		retrievelist(i,&e,books);
		if (strcmp(e.book.name,name)==0)
		{
			printf("The Book price: %d\n",e.book.price);
			printf("Buying succeeded",e.book.price);
            e.book.number--;
			saveBooks();
			a=1;
			break;
		}
	}
			
	if (!a)
	{
		printf("Book not found.\n");
		return;
	}
}

void requestNewBook()
{
	listentry e;
	NewBookRequest NBR;
    char name[50];
	char author[50];
	
	getchar();
	printf ("Enter Book name to recommend: ");
	gets(name);
	
	getchar();
	printf ("Enter author name: ");
	gets(author);
	
	strcpy(NBR.name,name);
	strcpy(NBR.author,author);
	
	e.NBR=NBR;
	insertlist (listsize(NBRs),e,NBRs);
}

void viewBorrowRequests(char username[])
{
	for (int i=0;i<listsize(BRs);i++)
    {
		listentry e;
		retrievelist(i,&e,BRs);
		if (strcmp(e.BR.user.username,username)==0)
		{
			printf("Request information:\n1. Book: %s\n2. status: %s\n--------------------------------\n",e.BR.book.name,e.BR.status?(e.BR.status==1?"approved":"denied"):"waiting");
		}
	}
}