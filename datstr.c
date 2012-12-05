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

void freeUsers(struct User *array, int size){
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
						if(ptr->data->bookTitle!=NULL){
							free(ptr->data->bookTitle);
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
						if(ptr->data->bookTitle!=NULL){
							free(ptr->data->bookTitle);
						}
						free(ptr->data);
					}
					temp=ptr;
					ptr=ptr->next;
					free(temp);
				}
			}
		}
	}
}
