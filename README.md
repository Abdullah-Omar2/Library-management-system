
# Library Management System

## Project Overview

This project is a Library Management System implemented in C. The system allows for dynamic management of books, users, and admins, with features for making and processing book borrow requests, returning books, and viewing user data.

## Features

- **User Management**: Register new users, view user data.
- **Book Management**: Add new books, view book details, and manage book borrow requests.
- **Admin Management**: Admins can approve or deny book borrow requests, add or remove books, and manage user data.
- **File Handling**: Persistent storage of users, books, borrow requests, and new book requests using text files.

## Project Structure

```
project/
├── admin.c
├── admin.h
├── admins.txt
├── books.txt
├── borrowrequests.txt
├── global.h
├── library.c
├── library.h
├── list.c
├── list.h
├── main.c
├── main.exe
├── newbookrequests.txt
├── owner.c
├── owner.h
├── user.c
├── user.h
├── users.txt
```

### Main Components

- **admin.c & admin.h**: Functions and structures related to admin functionalities.
- **user.c & user.h**: Functions and structures related to user functionalities.
- **library.c & library.h**: Core library management functions and definitions.
- **list.c & list.h**: Implementation of lists used for managing books, users, and requests.
- **global.h**: Global definitions and structures.
- **main.c**: Entry point of the application.

### Data Files

- **admins.txt**: Stores admin data.
- **books.txt**: Stores book data.
- **borrowrequests.txt**: Stores borrow request data.
- **newbookrequests.txt**: Stores new book request data.
- **users.txt**: Stores user data.

## Usage

1. **Compiling the Project**:
   To compile the project, you can use the following command:
   ```
   gcc main.c library.c admin.c user.c list.c -o main.exe
   ```

2. **Running the Project**:
   After compiling, you can run the project using:
   ```
   main.exe
   ```

## Functions

### User Functions

- `makeReservation()`: Allows a user to make a book reservation.
- `returnReservedBook()`: Allows a user to return a reserved book.
- `viewUsers()`: Displays a list of all users.
- `viewUserData(char username[])`: Displays data of a specific user.

### Admin Functions

- `approveRequest(BorrowRequest request)`: Approves a book borrow request.
- `denyRequest(BorrowRequest request)`: Denies a book borrow request.
- `addNewBook(Book book)`: Adds a new book to the library.
- `removeBook(char bookID[])`: Removes a book from the library.

## File Handling

The project uses text files to persist data between sessions. Functions for handling borrow requests and new book requests are implemented in `library.c`.

## Video Explanation

For a detailed explanation of the project, you can watch the video [here](https://drive.google.com/file/d/159AV5efqfHAZRA1AX-48UAmWL2seTmjd/view?usp=drive_link).


