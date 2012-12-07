#ifndef DATSTR_H
#define DATSTR_H

#include <pthread.h>
/*stores the orders so we can print them out at the end*/
struct Order
{
	char * bookTitle;
	float cost;
	float currentCredits;
};

/*used to make generic linked lists*/
struct Node
{
	void * data;
	struct	Node * next;
};

/*stroes data for each user*/
struct User{
	char * username;
	int uid;
	double remainingCredits;
	pthread_mutex_t* userMutex;
	struct Node * success;
	struct Node * fail;
};

/*struct to give to consumer threads when they're created*/
struct ConsumerThreadData{
	struct User **users;
	char *input;
	int usersSize;
};


struct User* createUser(char *username,int uid,double initialCredits);
void freeUsers(struct User **array, int size);


#endif
