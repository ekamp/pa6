#include<stdio.h>
#include<stdlib.h>


struct User createUser(char *username,int uid,double initialCredits)
{
	struct User newUser = calloc(1,sizeof(struct User));
	newUser->username = username;
	newUser->uid = uid;
	newUser->initialCredits = initialCredits;
	pthread_mutex_init(newUser->userMutex,NULL);
}

void freeUsers(struct User *head, int size){





}


