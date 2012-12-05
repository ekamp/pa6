#ifndef BOOKORDERS_H
#define BOOKORDERS_H


/*create the user database*/
struct User * openDatabase (FILE * dbFile, int* size);

/*producer thread creates the consumer threads here*/
void openOrders (FILE * bookOrderFile,struct User *users, int size);

/*prints the output file*/
void printToFile (Node* userArray, int size);

/*helper function to open orders*/
void purchase(struct Node * success, struct Node * fail,struct User * currentUser,double cost,char *bookTitle)

/*the function called by the consumer threads*/
void consumer(struct ConsumerThreadData* data);

#endif
