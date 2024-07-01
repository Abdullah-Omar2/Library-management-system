#include <stdio.h>
#include <string.h>
#include "library.h"

void viewUserData(char username[]);
void changePassword(char username[]);
void viewBooks();
void searchBook();
void requestBorrow(char username[]);
void buyBook();
void requestNewBook();
void viewBorrowRequests(char username[]);

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
                viewBooks();
                return a;
            case 4:
                searchBook();
                return a;
            case 5:
                requestBorrow(username);
                return a;
            case 6:
                buyBook();
                return a;
            case 7:
                requestNewBook();
                return a;
            case 8:
                viewBorrowRequests(username);
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
				printf("  Book %d: %s\n",j+1,e.user.borbk[j]);
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

void requestBorrow(char username[])
{
	listentry br,u,bo;
	
	for (int i=0;i<listsize(users);i++)
	{
        retrievelist(i,&u,users);
        if (u.user.username==username)
		{
            if (u.user.nbor>=2)
			{
				printf ("you are already borrow two books, you can't borrow again.\n");
				return;
			}
			break;
        }
    }
	
	int a;
	char bookname[50];
	getchar();
	printf ("Enter book name to borrow: ");
	gets(bookname);
	
	for (int i=0;i<listsize(books);i++)
	{
		retrievelist(i,&bo,books);
		if (strcmp(bo.book.name,bookname)==0)
		{
			a=1;
			break;
		}
	}
	
	if (!a)
	{
		printf("Book not found.\n");
		return;
	}
	
	strcpy(br.BR.username,u.user.username);
	strcpy(br.BR.bookname,bo.book.name);
	br.BR.status=0;
	insertlist (listsize (BRs),br,BRs);
	saveBorrowRequests();
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
			printf("Buying succeeded\n");
            e.book.number--;
			replacelist(i,e,books);
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
	saveNewBookRequests();
}

void viewBorrowRequests(char username[])
{
	for (int i=0;i<listsize(BRs);i++)
    {
		listentry e;
		retrievelist(i,&e,BRs);
		if (strcmp(e.BR.username,username)==0)
		{
			printf("Request information:\n1. Book: %s\n2. status: %s\n--------------------------------\n",e.BR.bookname,(e.BR.status?(e.BR.status==1?"approved":"denied"):"waiting"));
		}
	}
}