#include <stdio.h>
#include "library.h"

 void initializeLibrary()
{
    createlist(&books);
    createlist(&users);
    createlist(&admins);
    createlist(&BRs);
    createlist(&NBRs);
    loadBooks();
    loadUsers();
    loadAdmins();
	loadBorrowRequests();
	loadNewBookRequests();
}

void loadBooks()
{
    FILE *file=fopen("books.txt","r");
    if (file==NULL)
	{
        printf("Error loading books.\n");
        return;
    }

    createlist(&books);

    listentry e;
    while (fscanf(file,"%49[^,],%49[^,],%d,%d\n",e.book.name,e.book.author,&e.book.price,&e.book.number)!=EOF)
	{
        insertlist(listsize(books),e,books);
    }

    fclose(file);
}

void saveBooks()
{
    FILE *file=fopen("books.txt","w");
    if (file==NULL)
	{
        printf("Error saving books.\n");
        return;
    }

    listentry e;
    for (int i=0;i<listsize(books);i++)
	{
        retrievelist(i,&e,books);
        fprintf(file,"%s,%s,%d,%d\n",e.book.name,e.book.author,e.book.price,e.book.number);
    }

    fclose(file);
}

void loadUsers()
{
    FILE *file=fopen("users.txt","r");
    if (file==NULL)
	{
        printf("Error loading users.\n");
        return;
    }

    createlist(&users);

    listentry e;
    while (fscanf(file,"%d,%49[^,],%49[^,],%d,%49[^,],%49[^\n]\n",&e.user.id,e.user.username,e.user.pass,&e.user.nbor,e.user.borbk[0],e.user.borbk[1])!=EOF)
	{
        insertlist(listsize(users),e,users);
    }

    fclose(file);
}

void saveUsers()
{
    FILE *file=fopen("users.txt","w");
    if (file==NULL)
	{
        printf("Error saving users.\n");
        return;
    }

    listentry e;
    for (int i=0;i<listsize(users);i++)
	{
        retrievelist(i,&e,users);
        fprintf(file,"%d,%s,%s,%d,%s,%s\n",e.user.id,e.user.username,e.user.pass,e.user.nbor,e.user.borbk[0],e.user.borbk[1]);
    }

    fclose(file);
}

void loadAdmins()
{
    FILE *file=fopen("admins.txt","r");
    if (file==NULL)
	{
        printf("Error loading admins.\n");
        return;
    }

    createlist(&admins);

    listentry e;
    while (fscanf(file,"%49[^,],%49[^,],%d,%d,%d\n",e.admin.adminname,e.admin.pass,&e.admin.permissions[0],&e.admin.permissions[1],&e.admin.permissions[2])!=EOF)
	{
        insertlist(listsize(admins),e,admins);
    }

    fclose(file);
}

void saveAdmins()
{
    FILE *file=fopen("admins.txt","w");
    if (file==NULL)
	{
        printf("Error saving admins.\n");
        return;
    }

    listentry e;
    for (int i=0;i<listsize(admins);i++)
	{
        retrievelist(i,&e,admins);
        fprintf(file,"%s,%s,%d,%d,%d\n",e.admin.adminname,e.admin.pass,e.admin.permissions[0],e.admin.permissions[1],e.admin.permissions[2]);
    }

    fclose(file);
}

void loadBorrowRequests()
{
    FILE *file=fopen("borrowrequests.txt","r");
    if (file==NULL)
	{
        printf("Error loading borrow requests.\n");
        return;
    }

    createlist(&BRs);

    listentry e;
    while (fscanf(file,"%49[^,],%49[^,],%d\n",e.BR.username,e.BR.bookname,&e.BR.status)!=EOF)
	{
        insertlist(listsize(BRs),e,BRs);
    }

    fclose(file);
}

void saveBorrowRequests()
{
    FILE *file=fopen("borrowrequests.txt","w");
    if (file==NULL)
	{
        printf("Error saving borrow requests.\n");
        return;
    }

    listentry e;
    for (int i=0;i<listsize(BRs);i++)
	{
        retrievelist(i,&e,BRs);
        fprintf(file,"%s,%s,%d\n",e.BR.username,e.BR.bookname,e.BR.status);
    }

    fclose(file);
}

void loadNewBookRequests()
{
    FILE *file=fopen("newbookrequests.txt","r");
    if (file==NULL)
	{
        printf("Error loading new book requests.\n");
        return;
    }

    createlist(&NBRs);

    listentry e;
    while (fscanf(file,"%49[^,],%49[^\n]\n",e.NBR.name,e.NBR.author)!=EOF)
	{
        insertlist(listsize(NBRs),e,NBRs);
    }

    fclose(file);
}

void saveNewBookRequests()
{
    FILE *file=fopen("newbookrequests.txt","w");
    if (file==NULL)
	{
        printf("Error saving new book requests.\n");
        return;
    }

    listentry e;
    for (int i=0;i<listsize(NBRs);i++)
	{
        retrievelist(i,&e,NBRs);
        fprintf(file,"%s,%s\n",e.NBR.name,e.NBR.author);
    }

    fclose(file);
}

void closeLibrary()
{
    saveBooks();
    saveUsers();
    saveAdmins();
	saveBorrowRequests();
	saveNewBookRequests();
    destroylist(&books);
    destroylist(&users);
    destroylist(&admins);
    destroylist(&BRs);
    destroylist(&NBRs);
}