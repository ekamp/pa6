#include<stdio.h>
#include<stdlib.h>
#include "datstr.h"

struct User* createUser(char *username,int uid,double initialCredits)
{
	struct User* newUser =(struct User *) calloc(1,sizeof(struct User));
	newUser->username = username;
	newUser->uid = uid;
	newUser->remainingCredits = initialCredits;
	newUser->userMutex = (pthread_mutex_t*)calloc(1,sizeof(pthread_mutex_t));
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
				free(array[i]->userMutex);
				if(array[i]->success!=NULL){
					ptr = array[i]->success->next;
					while(ptr!=array[i]->success){
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
					if (ptr->data!=NULL){
						if(((struct Order*)(ptr->data))->bookTitle!=NULL){
							free(((struct Order*)ptr->data)->bookTitle);
						}
						free(ptr->data);
					}
					free(ptr);					
				}
				if(array[i]->fail!=NULL){
					ptr = array[i]->fail->next;
					while(ptr!=array[i]->fail){
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
					if (ptr->data!=NULL){
						if(((struct Order*)ptr->data)->bookTitle!=NULL){
							free(((struct Order*)ptr->data)->bookTitle);
						}
						free(ptr->data);			
					}				
					free(ptr);
				}
				free(array[i]);
			}
		}
		free(array);
	}
}
