#include <stdio.h>
#include <string.h>

void openFiles (FILE * dbFile , FILE * bookOrderFile)
{
	/*opens the two database files. dbFile is the database of users and 
	 * bookOrderFile is the database of all the books offered and their prices*/
}

double bookCost(char *bookTitle)
{
	/*Searches through the database for the cost of a book*/
} 

double purchase(char *bookTitle,struct user username)
{   /* Adds the book order to the database and subtracts the cost of the book
	 * from the user's account and returns the amount the user has left in his account
	 * or if the user does not have enough for the book returns -1*/
}

void printReceipt(char * bookTitle,int bookCredit,int userCredit)
{
	/*After purchasing a book the user gets a printed receipt*/
	
}
