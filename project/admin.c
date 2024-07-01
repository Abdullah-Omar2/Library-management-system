#include <stdio.h>
#include <string.h>
#include "library.h"

void viewUsers();
void viewBooks();
void adminAddBook(char username[]);
void adminRemoveBook(char username[]);
void adminAddUser(char username[]);
void adminRemoveUser(char username[]);
void editUserId();
void searchBook();
void adminMakeReservation(char username[]);

int adminMode()
{
	int a=0;
    char username[50],password[50];
    printf("Enter Admin username: ");
    scanf("%s",username);
    printf("Enter Admin password: ");
    scanf("%s",password);

    int q=0;
    for (int i=0;i<listsize(admins);i++)
	{
        listentry e;
        retrievelist(i,&e,admins);
        if (strcmp(e.admin.adminname,username)==0&&strcmp(e.admin.pass,password)==0)
		{
            q=1;
            break;
        }
    }

    if (q)
	{
        int choice;
        printf("Welcome Admin\n");
        printf("1. View Users\n2. View Books\n3. Add Book\n4. Remove Book\n5. Add User\n6. Remove User\n7. Edit User ID\n8. Search Book\n9. Make Reservation\n10. Logout\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                viewUsers();
                return a;
            case 2:
                viewBooks();
                return a;
            case 3:
                adminAddBook(username);
                return a;
            case 4:
                adminRemoveBook(username);
                return a;
            case 5:
                adminAddUser(username);
                return a;
            case 6:
                adminRemoveUser(username);
                return a;
            case 7:
                editUserId();
                return a;
            case 8:
                searchBook();
                return a;
            case 9:
                adminMakeReservation(username);
                return a;
            case 10:
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
        printf("Invalid username or passward.\n");
		return a;
    }
}

void viewUsers()
{
    printf("Users:\n");
    for (int i=0;i<listsize(users);i++)
	{
        listentry e;
        retrievelist(i,&e,users);
        printf("Username: %s\nID: %d\nPassword: %s\nNumber of Borrowed Books: %d\n",e.user.username,e.user.id, e.user.pass,e.user.nbor);
        printf("Borrowed Books:\n");
        for (int j=0;j<e.user.nbor;j++)
		{
            printf("  Book %d: %s\n",j+1,e.user.borbk[j]);
        }
    }
}

void viewBooks()
{
    printf("Books:\n");
    for (int i=0;i<listsize(books);i++)
	{
        listentry e;
        retrievelist(i,&e,books);
        printf("name: %s\nAuthor: %s\nnumber: %d\nPrice: %d$\n-------------------------------------------------\n",e.book.name,e.book.author,e.book.number,e.book.price);
    }
}

void adminAddBook(char username[])
{
	listentry e;
	for (int i=0;i<listsize(admins);i++)
	{
        retrievelist(i,&e,admins);
        if (strcmp(e.admin.adminname,username)==0)
		{
            break;
        }
    }
	
	if (e.admin.permissions[0])
	{
		Book newBook;
		getchar();
		printf("Enter Book name: ");
		gets(newBook.name);
		printf("Enter Book author: ");
		gets(newBook.author);
		printf("Enter Book number: ");
		scanf("%d",&newBook.number);
		printf("Enter Book price: ");
		scanf("%d",&newBook.price);
		
		for (int i=0;i<listsize(books);i++)
		{
			listentry e;
			retrievelist(i,&e,books);
			if (strcmp(e.book.name,newBook.name)==0)
			{
				printf ("Book is already in library.\n");
				return;
			}
		}
		
		listentry a;
		a.book=newBook;
		insertlist(listsize(books),a,books);
	
		saveBooks();
		printf("Book added successfully.\n");
	}
	else
	{
		printf("you don't have permission to that.\n");
	}
}

void adminRemoveBook(char username[])
{
	listentry e;
	for (int i=0;i<listsize(admins);i++)
	{
        retrievelist(i,&e,admins);
        if (strcmp(e.admin.adminname,username)==0)
		{
            break;
        }
    }
	
	if (e.admin.permissions[0])
	{
		char bookName[50];
		getchar();
		printf("Enter Book Name to remove: ");
		gets(bookName);
	
		for (int i=0;i<listsize(books);i++)
		{
			listentry e;
			retrievelist(i,&e,books);
			if (strcmp(e.book.name,bookName)==0)
			{
				deletlist(i,&e,books);
				saveBooks();
				printf("Book removed successfully.\n");
				return;
			}
		}
	
		printf("Book not found.\n");
	}
	else
	{
		printf("you don't have permission to that.\n");
	}
}

void adminAddUser(char username[])
{
	listentry e;
	for (int i=0;i<listsize(admins);i++)
	{
		retrievelist(i,&e,admins);
		if (strcmp(e.admin.adminname,username)==0)
		{
			break;
		}
	}
		
	if (e.admin.permissions[1])
	{
		User newUser;
		printf("Enter User username: ");
		scanf("%s",newUser.username);
		printf("Enter User ID: ");
		scanf("%d",&newUser.id);
		printf("Enter User password: ");
		scanf("%s",newUser.pass);
		newUser.nbor=0;
		
		for (int i=0;i<listsize(users);i++)
		{
			listentry e;
			retrievelist(i,&e,users);
			if (strcmp(e.user.username,newUser.username)==0||strcmp(e.user.pass,newUser.pass)==0||e.user.id==newUser.id)
			{
				printf("Username or ID or Passward is already used try again.\n");
				adminAddUser(username);
				return;
			}	
		}
	
		listentry e;
		e.user=newUser;
		insertlist(listsize(users),e,users);
	
		saveUsers();
		printf("User added successfully.\n");
	}
	else
	{
		printf("you don't have permission to that.\n");
	}	
}

void adminRemoveUser(char username[])
{
	listentry e;
	for (int i=0;i<listsize(admins);i++)
	{
		retrievelist(i,&e,admins);
		if (strcmp(e.admin.adminname,username)==0)
		{
			break;
		}
	}
		
	if (e.admin.permissions[1])
	{
		int userID;
		printf("Enter User ID to remove: ");
		scanf("%d",&userID);
	
		for (int i=0;i<listsize(users);i++)
		{
			listentry e;
			retrievelist(i,&e,users);
			if (e.user.id==userID)
			{
				deletlist(i,&e,users);
				saveUsers();
				printf("User removed successfully.\n");
				return;
			}	
		}
	
		printf("User not found.\n");
	}
	else
	{
		printf("you don't have permission to that.\n");
	}	
}

void editUserId()
{
    int oldID,newID;
    printf("Enter old User ID: ");
    scanf("%d",&oldID);
    printf("Enter new User ID: ");
    scanf("%d",&newID);
	
	for (int i=0;i<listsize(users);i++)
	{
        listentry e;
        retrievelist(i,&e,users);
        if (e.user.id==newID)
		{
            printf("ID is already used try again.\n");
            editUserId();
			return;
        }
    }

    for (int i=0;i<listsize(users);i++)
	{
        listentry e;
        retrievelist(i, &e, users);
        if (e.user.id==oldID)
		{
            e.user.id=newID;
            replacelist(i,e,users);
            saveUsers();
			printf("User ID updated successfully.\n");
            return;
        }
    }

    printf("User not found.\n");
}

void searchBook()
{
	int c;
	char name[50];
	char author[50];
	printf ("1. search by name\n2. search by author\n");
	scanf("%d",&c);
	
	switch(c)
	{
		case 1:
			getchar();
			printf("Enter Book name to search: ");
			gets(name);

			for (int i=0;i<listsize(books);i++)
			{
				listentry e;
				retrievelist(i,&e,books);
				if (strcmp(e.book.name,name)==0)
				{
					printf("Name: %s, Author: %s, Number: %d, Price: %d$\n",e.book.name,e.book.author,e.book.number,e.book.price);
					return;
				}
			}
			
			printf("Book not found.\n");
			break;
		case 2:
			getchar();
			printf("Enter Book author to search: ");
			gets(author);
			
			int authorFound=0;

			for (int i=0;i<listsize(books);i++)
			{
				listentry e;
				retrievelist(i,&e,books);
				if (strcmp(e.book.author,author)==0)
				{
					printf("Name: %s, Author: %s, Number: %d, Price: %d$\n-------------------\n",e.book.name,e.book.author,e.book.number,e.book.price);
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
}

void adminMakeReservation(char username[])
{
	listentry e;
	for (int i=0;i<listsize(admins);i++)
	{
		retrievelist(i,&e,admins);
		if (strcmp(e.admin.adminname,username)==0)
		{
			break;
		}
	}
	
	if (e.admin.permissions[2])
	{
		if (listsize(BRs)==0)
		{
			printf("No borrow requests.\n");
			return;
		}
		
		printf("Borrow Requests:\n");
		for (int i=0;i<listsize(BRs);i++)
		{
			listentry e;
			retrievelist(i,&e,BRs);
			printf("Request %d:\n",i+1);
			printf("  User name: %s\n",e.BR.username);
			printf("  Book name: %s\n",e.BR.bookname);
			printf("--------------------------------------\n");
		}
		listentry br,u,bo;
		
		int requestNumber;
		printf ("Enter namber of request you want to take action: ");
		scanf ("%d",&requestNumber);
		
		if (requestNumber<1||requestNumber>listsize(BRs))
		{
			printf("Invalid request number.\n");
			return;
		}
		
		retrievelist(requestNumber-1,&br,BRs);
		if (br.BR.status!=0)
		{
			printf("This request has already been handled.\n");
			return;
		}
	
		int pu;
		for (pu=0;pu<listsize(users);pu++)
		{
			retrievelist(pu,&u,users);
			if (strcmp(u.user.username,br.BR.username)==0)
			{
				break;
			}
		}
	
		if (u.user.nbor>=2)
		{
			printf("User is already borrowing two books.\n");
			return;
		}	
	
		int pb;
		for (pb=0;pb<listsize(books);pb++)
		{
			retrievelist(pb,&bo,books);
			if (strcmp(bo.book.name,br.BR.bookname)==0)
			{
				break;
			}
		}
	
		int c;
		printf ("Enter 1 to accept or 2 to deny: ");
		scanf ("%d",&c);
	
		if (c==1)
		{
			strcpy(u.user.borbk[u.user.nbor],br.BR.bookname);
			u.user.nbor++;
			bo.book.number--;
			br.BR.status=1;
			replacelist(pu,u,users);
			replacelist(pb,bo,books);
			replacelist(requestNumber-1,br,BRs);
			saveUsers();
			saveBooks();
			saveBorrowRequests();
			printf("Request accepted.\n");
		}
		else if (c==2)
		{
			br.BR.status=-1;
			replacelist(requestNumber-1,br,BRs);
			saveBorrowRequests();
			printf("Request denied.\n");		
		}
		else
		{
			printf("Invalid action.\n");
			return;
		}
	}
	else
	{
		printf("you don't have permission to that.\n");
	}	
}
