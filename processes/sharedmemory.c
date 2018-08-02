/*
	KYANDE MICHAEL JOHN.
	P15/34906/2014.
	ASSIGNMENT 1.
	CSC_322.
	A PARENT SPAWNS 5 CHILDREN AND THE CHILDREN COMMUNICATE VIA A SHARED MEMORY.
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main()
{
	// variables.
	int n = 5;// number of children;
	__pid_t p; // variable to hold fork function reply.
	__pid_t processes[5]; // hold process IDs.
	key_t children_key = 0512; // key to create child shared memory.
	char *parent; // pointer to shared memory.
	char *child; // pointer to shared memory.

	//int parent_id = shmget(parent_key, 1024, 0666|IPC_CREAT); // create shared memory.
	int children_id = shmget(children_key, 1024, 0666|IPC_CREAT); // create shared memory.
	//int parent_id = shmget(children_key, 1024, 0444|IPC_CREAT); // create shared memory.
	
 	// error check.
	// if(parent_id == -1){
	// 	// create memory has failed.
	// 	fprintf(stderr, "Parent is not connected to shared memory.\n");
	// 	exit(1);
	// } 
	// else {
	// 	fprintf(stderr, "Parent is connected to shared memory with id is: %d\n", parent_id);
	// }
	//error check.
	if(children_id == -1){
		// create memory has failed.
		fprintf(stderr, "Child is not connected to shared memory.\n");
		exit(1);
	} else {
		fprintf(stderr, "Child is connected to shared memory with id is: %d\n", children_id);
	}

	//spawn 5 children.
	// print parent process Id.
	printf("I'm the parent and my pid is: %d\n\n", getpid());

	for (int i = 0; i < n; ++i){
		p = fork();

		processes[i] = p;

		//printf("%d\n", p);
		// error checking.
		if(p < 0){
			//forking has failed.
			fprintf(stderr, "Child process not created.\n");
		} else if(p == 0){
			// children processes.
			child = (char*) shmat(children_id,(void*)0,0); // attach pointer to shared memory.
			//sleep(1);
			printf("Child is reading... =>  %s\n",child);
			// print child process ID and parent ID.
			sprintf(child,"Child %d process Id is %d and parent ID is %d ", i + 1, getpid(), getppid());

			//print data
			printf("Data written in memory: %s\n",child);

        	_exit(0);//exit the child process to prevent further forking.

		} else {
			// parent process.
			parent = (char*) shmat(children_id,(void*)0,0); // attach pointer to shared memory
			// show data in shared memory.
			sleep(1);
			printf("Parent is reading... => %s\n\n",parent);
			// test if parent can write to memory.
			//sprintf(child, "test data");

		} 
		wait(NULL);// wait for processes to terminate.
	}	
	// wait for processes to terminate.
	// for (int i = 0; i < n; ++i)
	// {
	// 	int status;
	// 	waitpid(processes[i], &status, 0);
	// 	printf("Process %d exited with return code %d\n", processes[i], WEXITSTATUS(status));
	// }
	// destroy both shared memories
    //shmctl(parent_id,IPC_RMID,NULL);
    //detach from shared memory 
	shmdt(child);
	//detach from memory
	shmdt(parent);
    shmctl(children_id,IPC_RMID,NULL);

	// exit main program.
	return 0;
}