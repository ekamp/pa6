
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
	
	if(dbFile == NULL)
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
	if(bookOrderFile == NULL || users == NULL)
	{
		return;
	}
	while(getline(&input,&length,bookOrderFile) != -1)
	{
		strcpy(booTitle,strtok(input,"|"));
		strcpy(cost,strtok(NULL,"|"));
		strcpy(uid,strtok(NULL,"|"));
		
		//newUser = createUser(username,uid,atof(credits));
	}
	
	
}


void printToFile (Node[] userArray)
{
	int i = 0;
	if (userArray == NULL)
	{
		return;
	}
	else
	{
		while(userArray[i] != NULL)
		{
			printf("%s",(char *)userArray[i]->data->username);
			while(userArray[i]
			printf("=== BEGIN CUSTOMER INFO ===\n");
			
		}
		
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

struct Order createOrder(char *bookTitle,double cost, int uid,)
{
	struct User newUser = calloc(1,sizeof(struct User));
	newUser->username = username;
	newUser->uid = uid;
	newUser->initialCredits = initialCredits;
	pthread_mutex_init(newUser->userMutex,NULL);
}
