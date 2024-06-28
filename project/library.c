#include <stdio.h>
#include "library.h"

 void initializeLibrary()
{
    createlist(&books);
    createlist(&users);
    createlist(&admins);
    loadBooks();
    loadUsers();
    loadAdmins();
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
    while (fscanf(file,"%d,%49[^,],%49[^,],%d\n",&e.user.id,e.user.username,e.user.pass,&e.user.nbor)!=EOF)
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
        fprintf(file,"%d,%s,%s,%d\n",e.user.id,e.user.username,e.user.pass,e.user.nbor);
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
    while (fscanf(file,"%49[^,],%49[^\n]\n",e.admin.adminname,e.admin.pass)!=EOF)
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
        fprintf(file,"%s,%s\n",e.admin.adminname,e.admin.pass);
    }

    fclose(file);
}

void closeLibrary()
{
    saveBooks();
    saveUsers();
    saveAdmins();
    destroylist(&books);
    destroylist(&users);
    destroylist(&admins);
}