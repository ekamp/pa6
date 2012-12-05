#include <stdio.h>
#include "helper.c"
#include <string.h>
#include "bookOrders.h"

int main(int argc, char **argv)
{	
	struct User* users;/*the user database*/
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
		fclose(dbfile);
		fclose(orderFile);
		return 0;
	}

	/*This should populate the orders within the users*/
	openOrders(orderFile,users,size);
	
	fclose(dbfile);
	fclose(orderFile);
	printToFile(users);
	freeUsers(users);
	return 0;
}

/*create the user database*/
struct User * openDatabase (FILE * dbFile, int* size)
{
	size_t length = 0;
	char * input;
	char * part;
	int largest = 0 ;
	struct User *newUser;
	struct Node *tail;
	struct Node *temp;
	struct Node *it;
	struct User *userList;
	char * username;
	char * uid;
	char * credits;
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
		newUser = createUser(username,uid,atof(credits));
		if (atoi(newUser->uid) > largest)
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

	userList = calloc(largest+1,sizeof(struct User));
	it = tail->next;
	*size=largest+1;

	while(it != tail)
	{
		userList[it->data->uid] = it->data;
		temp = it;
		it = it->next;
		free(temp);
	}
	userList[it->data->uid] = it->data;
	free(it);
	return userList; 
}



/*producer thread creates the consumer threads here*/
void openOrders (FILE * bookOrderFile,struct User *users)
{
	/*Book title | cost | userID | category */ 
	size_t length = 0;
	char * input;
	char * bookTitle;
	char * cost;
	char * uid;
	struct Node * temp;
	struct User * currentUser;
	if(bookOrderFile == NULL || users == NULL)
	{
		return;
	}
	while(getline(&input,&length,bookOrderFile) != -1)
	{

	/*start consumer thread, feed it a struct containing the input line which contains a single order and the pointer to the user database*/
	
	/*set input to NULL so getline will allocate new memory for every order, the consumer threads are responsible for freeing their input strings*/
	input=NULL;	




		/*
		 *  This part needs to go in the consumer threads:
		 *
		 *	strcpy(bookTitle,strtok(input,"|"));
		 *	strcpy(cost,strtok(NULL,"|"));
		 *	strcpy(uid,strtok(NULL,"|"));
		 *	
		 *	currentUser = (struct User)users[atoi(uid)];
		 *	purchase(currentUser->success, currentUser->fail,currentUser,cost,bookTitle);
		 */
	}
}

/*prints the output file*/
void printToFile (Node* userArray)
{
	int i = 0;
	int length;
	if (userArray == NULL)
	{
		return;
	}
	else
	{
/*this isn't going to work, we'll fix it later*/
		length = sizeof(userArray)/sizeof(struct Node);
		while(i<length)
		{
			printf("%s",(char *)userArray[i]->data->username);
			printf("=== BEGIN CUSTOMER INFO ===\n");
			printf("### BALANCE ###\n");
			printf("Customer name: %f",userArray[i]->data->username);
			printf("Customer ID number: %f",userArray[i]->data->uid);
			printf("Remaining credit balance after all purchases (a dollar amount): %d",userArray[i]->data->remainingCredits);
			i++;
		}

	}
}

/*helper function to open orders*/
void purchase(struct Node * success, struct Node * fail,struct User * currentUser,double cost,char *bookTitle)
{
	struct Node *temp;
	struct order *orderTemp;
	if (currentUser->remainingCredits - cost < 0)
	{
		/*Add to the fail node list */
		temp = calloc(1,sizeof(struct Node));
		order = calloc(1,sizeof(struct order));
		order->bookTitle = bookTitle;
		order->cost = cost;
		order->currentCredits = currentUser->remainingCredits;
		temp->data = order;
		fail->next = temp;
	}
	else
	{
		/* Add to the success node list */
		temp = calloc(1,sizeof(struct Node));
		order = calloc(1,sizeof(struct order));
		order->bookTitle = bookTitle;
		order->cost = cost;
		order->currentCredits = currentUser->remainingCredits-cost;
		temp->data = order;
		success->next = temp;
	}
}

