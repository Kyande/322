/* 
	KYANDE MICHAEL JOHN.
	P15/34906/2014.
	ASSIGNMENT 1.
	CSC_322.
	A PARENT SPAWNS 5 CHILDREN AND THE CHILDREN COMMUNICATE VIA MESSAGE QUEUES.
*/
#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/wait.h>
#include <sys/msg.h>
//#include <string.h>

struct message{
	long type; // message type.
	char text[100]; // message content.
};

int main(int argc, char const *argv[])
{
	int n = 5; // number of children processes.
	__pid_t p; // hold fork return value.
	__pid_t processes[n]; // hold children unique Id.
	key_t key = 8140; // unique ID to describe the message queue.
	struct message mess; // initialize message struct.

	int queue_id = msgget(key, 0600|IPC_CREAT); // create message queue and return identifier.

	// print parent process Id.
	printf("I'm the parent and my pid is: %d\n", getpid());

	// fork 5 children processes.
	for (int i = 0; i < n; ++i){
		
		p = fork(); // fork from main process.

		processes[i] = p; // store process ID.

		if(p < 0){
			// fork has failed.
			fprintf(stderr, "Child process not created.\n");
		} else if (p == 0){
			// child process.
			// send message to queue.
			if(i>0){
				/* code */
				msgrcv(queue_id, &mess, sizeof(mess), 1, 0); // read from message in queue
				printf("Child number(%d) read: %s\n", i + 1, mess.text);
			}

			mess.type = 1;
			sprintf(mess.text, "I'm process number %d and my id is %d \n",i+1 ,getpid());

			msgsnd(queue_id, &mess, sizeof(mess), 0);

			_exit(0);
		} else {
			// parent process.
		}

		wait(NULL); // wait for process to terminate.

	}

	return 0;
}