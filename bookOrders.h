#ifndef WORDSTAT_H
#define WORDSTAT_H


/*The user struct that holds user information, the user id stored in uid and current credit count*/
struct user{
	char * username;
	int uid;
	int cedits;
};
/*Book struct that holds the book title and the amount in credits it costs to purchase the book*/
struct book{
	char * bookTitle;
	int cedits;
	char * category;
};

void openFiles (FILE * dbFile , FILE * bookOrderFile)
{
	/*opens the two database files. dbFile is the database of users and 
	 * bookOrderFile is the database of all the books offered and their prices*/
	
}

double bookCost(char *bookTitle);
int purchase(char *bookTitle,struct user username);
void printReceipt(char * bookTitle,int bookCredit,int userCredit)

#endif
