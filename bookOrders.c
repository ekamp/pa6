#define _GNU_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bookOrders.h"
#include <pthread.h>
#include <unistd.h>
#include "datstr.h"

int main(int argc, char **argv)
{	
	struct User** users;/*the user database*/
	int size; /*number of users in database*/
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
	if(dbFile==NULL){
		fprintf(stderr,"ERROR: failed to open user database file\n");
		return 0;
	}

	orderFile = fopen(argv[2],"r");
	if(orderFile==NULL){
		fprintf(stderr,"ERROR: failed to open orders file\n");
		fclose(dbFile);
		return 0;
	}

	users = openDatabase(dbFile, &size);

	if (users == NULL)
	{
		printf("ERROR: database creation failed\n");
		fclose(dbFile);
		fclose(orderFile);
		return 0;
	}

	/*This should populate the orders within the users*/
	openOrders(orderFile,users,size);

	fclose(dbFile);
	fclose(orderFile);
	printToFile(users,size);
	freeUsers(users,size);
	return 0;
}

/*create the user database*/
struct User ** openDatabase (FILE * dbFile, int* size)
{
	size_t length = 0;
	char * input = NULL;
	int largest = 0 ;
	struct User *newUser =NULL;
	struct Node *tail =NULL;
	struct Node *temp;
	struct Node *it;
	struct User **userList;
	char * username =NULL;
	char * uid = NULL;
	char * credits = NULL;
	int existUsersFlag=0;

	if (dbFile == NULL)
	{
		fprintf(stderr, "ERROR: invalid database file\n");/*shouldn't happen, this was checked in main*/
		return NULL;
	}

	/*username | userID | credits | address | state | zip*/
	while(getline(&input,&length,dbFile) != -1)
	{
		existUsersFlag=1;
		strcpy(username,strtok(input,"|"));
		strcpy(uid,strtok(NULL,"|"));
		strcpy(credits,strtok(NULL,"|"));
		newUser = createUser(username,atoi(uid),atof(credits));
		if (newUser->uid > largest)
		{
			largest = newUser->uid;
		}
		if (tail != NULL)
		{
			temp = calloc(1,sizeof(struct Node));
			temp->data = newUser;
			temp->next = tail->next;
			tail->next = temp;
			tail = temp;
		}
		else
		{
			/*Create a new node and add to the head */
			tail = calloc(1,sizeof(struct Node));
			tail->data = newUser;
			tail->next = tail;
		}
	}

	if (existUsersFlag==0){
		fprintf(stderr, "ERROR: no users in database\n");
		return NULL;
	}

	userList = calloc(largest+1,sizeof(struct User*));
	it = tail->next;
	*size=largest+1;

	while(it != tail)
	{
		userList[((struct User*)it->data)->uid] = ((struct User*)it->data);
		temp = it;
		it = it->next;
		free(temp);
	}
	userList[((struct User*)it->data)->uid] = ((struct User*)it->data);
	free(it);
	return userList; 
}



/*producer thread creates the consumer threads here*/
void openOrders (FILE * bookOrderFile,struct User **users, int size)
{
	size_t length = 0;
	char * input;
	struct ConsumerThreadData* data;	
	pthread_t id;	

	if(bookOrderFile == NULL || users == NULL)
	{
		return;
	}
	while(getline(&input,&length,bookOrderFile) != -1)
	{

		/*start consumer thread, feed it a struct containing the input line which contains a single order and the pointer to the user database*/
		data = (struct ConsumerThreadData*) calloc (1, sizeof(struct ConsumerThreadData));
		data->users = users;
		data->input = input;
		data->usersSize = size;

		pthread_create(&id, NULL, consumer, data);


		/*set input to NULL so getline will allocate new memory for every order, the consumer threads are responsible for freeing their input strings*/
		input=NULL;	

	}
}


void *consumer(void* dat){

	char *bookTitle, *cost, *uid;
	int id;
	struct ConsumerThreadData* data = (struct ConsumerThreadData*)dat;

	pthread_detach(pthread_self());

	bookTitle=strtok(data->input,"|");
	cost=strtok(NULL,"|");
	uid=strtok(NULL,"|");

	id = atoi(uid);
	if(id+1 > data->usersSize){
		return NULL;
	}
	pthread_mutex_lock(data->users[id]->userMutex);
	purchase(data->users[id]->success, data->users[id]->fail, data->users[id], atof(cost), bookTitle);
	pthread_mutex_unlock(data->users[id]->userMutex);
	return NULL;
}


/*prints the output file*/
void printToFile (struct User ** userArray,int length)
{
	int i = 0;
	struct Node *ptr;
	FILE* file = fopen ("w", "report.txt");
	if (userArray == NULL)
	{
		return;
	}
	else
	{
		while(i<length)
		{
			if(userArray[i]!=NULL){
				fprintf(file,"=== BEGIN CUSTOMER INFO ===\n");
				fprintf(file,"### BALANCE ###\n");
				fprintf(file,"Customer name: %s\n",userArray[i]->username);
				fprintf(file,"Customer ID number: %d\n",userArray[i]->uid);
				fprintf(file,"Remaining credit balance after all purchases (a dollar amount): %f\n",userArray[i]->remainingCredits);
				fprintf(file,"### SUCCESSFUL ORDERS ###\n");


				if(userArray[i]->success!=NULL){
					ptr=userArray[i]->success->next;
					while(ptr!=userArray[i]->fail){
						fprintf(file,"%s| %f| %f\n", ((struct Order*)ptr->data)->bookTitle, ((struct Order*)ptr->data)->cost, ((struct Order*)ptr->data)->currentCredits);
						ptr=ptr->next;
					}
					fprintf(file,"%s| %f| %f\n", ((struct Order*)userArray[i]->success->data)->bookTitle, ((struct Order *)userArray[i]->success->data)->cost, ((struct Order*)userArray[i]->success->data)->currentCredits);
				}



				fprintf(file,"### REJECTED ORDERS ###\n");
				if(userArray[i]->fail!=NULL){
					ptr=userArray[i]->fail->next;
					while(ptr!=userArray[i]->fail){
						fprintf(file,"%s| %f\n", ((struct Order*)ptr->data)->bookTitle, ((struct Order*)ptr->data)->cost);
						ptr=ptr->next;
					}
					fprintf(file,"%s| %f\n", ((struct Order*)userArray[i]->fail->data)->bookTitle, ((struct Order*)userArray[i]->fail->data)->cost);
				}
				fprintf(file,"=== END CUSTOMER INFO ===\n");
			}	
			i++;
		}
	}
}

/*helper function to open orders*/
void purchase(struct Node * success, struct Node * fail,struct User * currentUser,double cost,char *bookTitle)
{
	struct Node *temp;
	struct Order *order;
	if (currentUser->remainingCredits - cost < 0)
	{
		/*Add to the fail node list */
		temp = calloc(1,sizeof(struct Node));
		order = calloc(1,sizeof(struct Order));
		order->bookTitle = bookTitle;
		order->cost = cost;
		order->currentCredits = currentUser->remainingCredits;
		temp->data = order;
		temp->next = fail->next;
		fail->next = temp;
		fail = temp;
	}
	else
	{
		/* Add to the success node list */
		temp = calloc(1,sizeof(struct Node));
		order = calloc(1,sizeof(struct Order));
		order->bookTitle = bookTitle;
		order->cost = cost;
		currentUser->remainingCredits =	order->currentCredits = currentUser->remainingCredits-cost;
		temp->data = order;
		temp->next = success->next;
		success->next = temp;
		success = temp;
	}
}

