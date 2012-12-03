#include <stdio.h>
#include "helper.c"
#include <string.h>
#include "bookOrders.h"

int main(int argc, char **argv)
{	
	struct User[] users;
	FILE * dbFile;
	FILE  * orderFile;
	if (argc > 1)
	{
		if (strcmp(argv[1],"h") == 0)
		{
			printf("Help message!!\n");
			return 0;
		}	
	}	
	if (argc != 4)
	{
		printf("User entered in incorrect number of arguments\n");
		return 0;
	}
	dbFile = fopen(argv[1],"r");
	orderFile = fopen(argv[2],"r");
	
	users = openFiles (dbFile, orderFile);
	if (users == NULL)
	{
		printf("ERROR: Entered in invalid File name\n");
		return 0;
	}
	printToFile(users);
	
	return 0;
}
