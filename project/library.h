#ifndef LIBRARY
#define LIBRARY

#include "list.h"

plist books;
plist users;
plist admins;
plist BRs;
plist NBRs;

void initializeLibrary();
void loadBooks();
void saveBooks();
void loadUsers();
void saveUsers();
void loadAdmins();
void saveAdmins();
void closeLibrary();

#endif