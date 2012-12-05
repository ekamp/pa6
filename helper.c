#include<stdio.h>
#include<stdlib.h>

struct User * openDatabase (FILE * dbFile)
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
	
	if (dbFile == NULL)
	{
		return NULL;
	}

	/*username | userID | credits | address | state | zip*/
	while(getline(&input,&length,dbFile) != -1)
	{
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
	userList = calloc(largest+1,sizeof(struct User));
	it = tail->next;
	
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
		strcpy(booTitle,strtok(input,"|"));
		strcpy(cost,strtok(NULL,"|"));
		strcpy(uid,strtok(NULL,"|"));
		
        currentUser = (struct User)users[atoi(uid)];
	    purchase(currentUser->success, currentUser->fail,currentUser,cost,bookTitle);
	}
    fclose(bookOrderFile);
}


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

struct User createUser(char *username,int uid,double initialCredits)
{
	struct User newUser = calloc(1,sizeof(struct User));
	newUser->username = username;
	newUser->uid = uid;
	newUser->initialCredits = initialCredits;
	pthread_mutex_init(newUser->userMutex,NULL);
}
