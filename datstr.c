#include<stdio.h>
#include<stdlib.h>
#include "datstr.h"

struct User* createUser(char *username,int uid,double initialCredits)
{
	struct User* newUser =(struct User *) calloc(1,sizeof(struct User));
	newUser->username = username;
	newUser->uid = uid;
	newUser->remainingCredits = initialCredits;
	pthread_mutex_init(newUser->userMutex,NULL);
	return newUser;
}

void freeUsers(struct User **array, int size){
	int i = 0;
	struct Node *ptr, *temp;
	if(array!=NULL){
		for(i = 0 ; i<size ; i++){
			if(array[i]!=NULL){
				if(array[i]->username!=NULL){
					free(array[i]->username);
				}
				pthread_mutex_destroy(array[i]->userMutex);
				ptr = array[i]->success;
				while(ptr!=NULL){
					if (ptr->data!=NULL){
						if(((struct Order*)(ptr->data))->bookTitle!=NULL){
							free(((struct Order*)ptr->data)->bookTitle);
						}
						free(ptr->data);
					}
					temp=ptr;
					ptr=ptr->next;
					free(temp);
				}
				ptr = array[i]->fail;
				while(ptr!=NULL){
					if (ptr->data!=NULL){
						if(((struct Order*)ptr->data)->bookTitle!=NULL){
							free(((struct Order*)ptr->data)->bookTitle);
						}
						free(ptr->data);
					}
					temp=ptr;
					ptr=ptr->next;
					free(temp);
				}
				free(array[i]);
			}
		}
		free(array);
	}
}
