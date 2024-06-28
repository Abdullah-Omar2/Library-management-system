#include <stdio.h>
#include <string.h>
#include "library.h"

void addAdmin();
void removeAdmin();
void setAdminPermissions();
void viewUsers();
void viewBooks();
void ownerAddBook();
void ownerRemoveBook();
void ownerAddUser();
void ownerRemoveUser();
void editUserId();
void searchBook();
void ownerMakeReservation();

int ownerMode()
{
	int a=0;
    char username[50],passward[50];
    printf("Enter Owner username: ");
    scanf("%s",username);
    printf("Enter Owner password: ");
    scanf("%s",passward);

    if (strcmp(username,"Owner")==0&&strcmp(passward,"1234")==0)
	{
        int choice;
        printf("Welcome Owner\n");
        printf("1. Add Admin\n2. Remove Admin\n3. Set Admin Permissions\n4. View Users\n5. View Books\n6. Add Book\n7. Remove Book\n8. Add User\n9. removeUser\n10. Make Reservation\n11. Logout\n");
        scanf("%d",&choice);

        switch (choice)
		{
            case 1:
                addAdmin();
                return a;
            case 2:
                removeAdmin();
                return a;
            case 3:
                setAdminPermissions();
                return a;
			case 4:
                viewUsers();
                return a;
            case 5:
                viewBooks();
                return a;
            case 6:
                ownerAddBook();
                return a;
			case 7:
                ownerRemoveBook();
                return a;
            case 8:
                ownerAddUser();
                return a;
            case 9:
                ownerRemoveUser();
                return a;
			case 10:
                ownerMakeReservation();
                return a;
            case 11:
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

void addAdmin()
{
	Admin newAdmin;
    printf("Enter Admin username: ");
    scanf("%s",newAdmin.adminname);
    printf("Enter Admin password: ");
    scanf("%s",newAdmin.pass);

    for (int i=0;i<3;i++)
	{
        newAdmin.permissions[i]=0;
    }

    listentry e;
    e.admin=newAdmin;
    insertlist(listsize(admins),e,admins);

    saveAdmins();
    printf("Admin added successfully.\n");
}

void removeAdmin()
{
    char adminname[50];
    printf("Enter Admin adminname to remove: ");
    scanf("%s",adminname);

    for (int i=0;i<listsize(admins);i++)
	{
        listentry e;
        retrievelist(i,&e,admins);
        if (strcmp(e.admin.adminname,adminname)==0)
		{
            deletlist(i,&e,admins);
            saveAdmins();
            printf("Admin removed successfully.\n");
            return;
        }
    }

    printf("Admin not found.\n");
}

void setAdminPermissions()
{
    char adminname[50];
    printf("Enter admin name to set permissions: ");
    scanf("%s",adminname);

    for (int i=0;i<listsize(admins);i++)
	{
        listentry e;
        retrievelist(i,&e,admins);
        if (strcmp(e.admin.adminname,adminname)==0)
		{
            printf("Enter permissions (1 for yes, 0 for no):\n");
            printf("1. Add/Remove Member: ");
            scanf("%d",&e.admin.permissions[0]);
            printf("2. Add/Remove Book: ");
            scanf("%d",&e.admin.permissions[1]);
            printf("3. Make Reservation: ");
            scanf("%d",&e.admin.permissions[2]);

            replacelist(i,e,admins);
            saveAdmins();
            printf("Permissions set successfully.\n");
            return;
        }
    }

    printf("Admin not found.\n");			
}

void ownerAddBook()
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
	
	listentry e;
    e.book=newBook;
    insertlist(listsize(books),e,books);

    saveBooks();
    printf("Book added successfully.\n");
}

void ownerRemoveBook()
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

void ownerAddUser()
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
            ownerAddUser();
			return;
        }
    }

    listentry e;
    e.user=newUser;
    insertlist(listsize(users),e,users);

    saveUsers();
    printf("User added successfully.\n");
}

void ownerRemoveUser()
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

void ownerMakeReservation()
{
	if (listsize(BRs)==0)
	{
        printf("No borrow requests.\n");
        return;
    }
	
	listentry e;
	int c;
    printf("Borrow Requests:\n");
    for (int i=0;i<listsize(BRs);i++)
	{
        listentry e;
        retrievelist(i,&e,BRs);
        printf("Request %d:\n",i+1);
        printf("  User ID: %d\n",e.BR.user.id);
        printf("  Book Name: %s\n",e.BR.book.name);
        printf("  Book Author: %s\n",e.BR.book.author);
        printf("  User's number of borrowed books: %d\n",e.BR.user.nbor);
        printf("--------------------------------------\n");
    }
	
	int requestNumber;
	printf ("Enter namber of request you want to take action: ");
	scanf ("%d",&requestNumber);
	
	if (requestNumber<1||requestNumber>listsize(BRs))
	{
        printf("Invalid request number.\n");
        return;
    }
	
	retrievelist(requestNumber-1,&e,BRs);
	if (e.BR.status!=0)
	{
        printf("This request has already been handled.\n");
        return;
    }
	
	printf ("Enter 1 to accept or 2 to deny: ");
	scanf ("%d",&c);
	
	if (c==1)
	{
        if (e.BR.user.nbor<2)
		{
            e.BR.user.borbk[e.BR.user.nbor]=e.BR.book;
            e.BR.user.nbor++;
            e.BR.book.number--;
            e.BR.status=1;
			printf("Request accepted.\n");
        }
		else
		{
            printf("User is already borrowing two books, you can't accept.\n");
            return;
        }
    }
	else if (c==2)
	{
        e.BR.status=-1;
        printf("Request denied.\n");		
    }
	else
	{
        printf("Invalid action.\n");
        return;
    }

    replacelist(requestNumber-1,e,BRs);
	saveBooks();
    saveUsers();
}