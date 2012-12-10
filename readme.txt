Readme
Project 6
Erik Kamp
Eugene Foley
Group 1


The multithreaded book orders program starts by taking in the file arguments which are the book orders file,
users file and category file. If the user does not enter in all elements an error message appears. If the user en
ters in -h then the program tells you what it needs to run. 

After opening the files and assigning them a pointer the program then goes and reads the users into the database using the openDB function. Then the program continues and starts to look at the orders file.

The book orders file spawns a new thread for each order. The new thread takes in the user and the order read in f
rom getline. When the threads run only one thread at a time has the lock on the user. Therefore multiple threads 
can be running at a time because of the many users in the database and orders file. Once the thread is done with 
the user the user becomes unlocked and the thread waiting for the user wakes up and relocks the user. Additionall
y a semaphore is used to make sure all threads are done writting to the file. Once the semaphores value reaches  
then the producer thread knows that consumer threads are done writting to the database. Once done the data stored
in memory is then written and then freed.

In all our program is very efficent in time and memory. It is efficent in run time due to the multiple threads be
ing run at the same time over different users, as oppossed to running one thread that goes through all the users.
Additionally it is easy to search for users because they are stored in an array therefore a linear search time
is attained. Additionally it is effiecent with memory due to the fact that the array of users is a pointer to a
linked list and is not copied over, which would waste space if not allocated and freed properly.
