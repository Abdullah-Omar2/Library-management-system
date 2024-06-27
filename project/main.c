#include <stdio.h>
#include "library.h"
#include "owner.h"
#include "admin.h"
#include "user.h"

void main() 
{
	initializeLibrary();
	
	int mode;
	
	printf("Welcome to the Library Management System\n");
	printf("Select mode:\n1. Owner\n2. Admin\n3. User\n");
	scanf("%d",&mode);
	
    for (;;)
	{
		switch (mode)
		{
			case 1:
				if (!ownerMode())break;
				else goto end;
			case 2:
				if (!adminMode())break;
				else goto end;
			case 3:
				if (!userMode())break;
				else goto end;
			default:
				printf("Invalid mode selected.\n");
				break;
		}
	}
	end:

    closeLibrary();
}