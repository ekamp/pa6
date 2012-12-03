#include <stdio.h>
#include "helper.c"
#include <string.h>
#include "bookOrders.h"

int main(int argc, char **argv)
{	
	char * dbFile = argv[1];
	char * bookOrderFile = argv[2];
	char * categoryNames = argv[3];
	char * input;
	char * bookTitle;
	char * username;
	char * ch = NULL;
	size_t length = 0;
	FILE * dbFileStream;
	FILE * bookOrderFileStream;
	int remaining;
	
	
	dbFileStream = fopen(dbFile,"w+");
	bookOrderFileStream = fopen(bookOrderFile,"w+");
	
	/*Our Structure = */openFiles(dbFileStream,bookOrderFileStream); /*Should be done in another thread */
	/*printf("Database File: %s \n booOrderFile : %s \n category : %s \n", dbFile,bookOrderFile,categoryNames);*/
	getline(&input, &length, stdin);
    printf("Input : %s\n",input); 
	input[strlen(input)-1] = '\0';
	while (strcmp(input,"q") != 0)
	{
		if (strcmp(input, "h") == 0)
        {
            printf("To place a book order please enter in your [username] [Book Title] or q to quit when you are done\n");
            getline(&input,&length, stdin);
            input[strlen(input)-1] = '\0';
            continue;
        }
        else
        {
	        ch = strtok(input, " ");
			if (ch == NULL)
			{
				printf("No search items given! \n");
				getline(&input, &length, stdin);
				input[strlen(input)-1] = '\0';
				continue;
			}
			while (ch != NULL)
			{
			  printf("username: %s \n",ch);
			  username = ch;
			  ch = strtok(NULL, " ");
			  printf("Book title %s \n",ch);
			  bookTitle = ch;
			  ch = strtok(NULL, " ");
			  /*Spawn new thread here in order to take care of the order*/
			  remaining = purchase(bookTitle,username);
			  if (remaining == -1)
			  {
				  printf("You have insufficent funds for this book please add more money to your account\n");
				  /*Add to the unsuccessful book db entry */
			  }
			  else
			  {
				  printReceipt(bookTitle,bookCost(bookTitle),remaining);
				  /*Add to the successful book db entry */
			  }
			}
		}
		getline(&input, &length, stdin);
		input[strlen(input)-1] = '\0';
	}
	return 0;
}
