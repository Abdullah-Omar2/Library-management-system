#ifndef GLOBAL
#define GLOBAL

typedef struct
{
    char name[50];
    char author[50];
    int number;
    int price;
}Book;

typedef struct
{
    char username[50];
    int id;
    char pass[50];
    Book borbk[2];
    int nbor;
}User;

typedef struct
{
    char adminname[50];
    char pass[50];
    int permissions[3]; // 0: add/remove member, 1: add/remove book, 2: make reservation
}Admin;

typedef struct
{
    User user;
	Book book;
	int status; //0: waiting, 1: approved, -1: denied
}BorrowRequest;

typedef struct
{
    char name[50];
    char author[50];
}NewBookRequest;

typedef union
{
    Book book;
    User user;
    Admin admin;
	BorrowRequest BR;
	NewBookRequest NBR;
}elementtype;

#define MAXELEMENT 100

typedef elementtype listentry;
#define MAXLIST MAXELEMENT 

#endif