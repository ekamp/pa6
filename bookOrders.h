#ifndef WORDSTAT_H
#define WORDSTAT_H

struct Order
{
	char * bookTitle;
	float cost;
	float currentCredits;
}


struct Node
{
	void * data;
	Node * next;
}

struct User{
	char * username;
	int uid;
	double remainingCedits;
	pthread_mutex_t userMutex;
	struct Node * success;
	struct Node * fail;
};

/* Create linked list of users and then read the pointers into an array for random access*/
/* Store the orders within the user and at the end read out all the users and their orders */



void openFiles (FILE * dbFile , FILE * bookOrderFile);


#endif
