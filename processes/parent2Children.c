/*
	KYANDE MICHAEL JOHN.
	P15/34906/2014.
	ASSIGNMENT 1.
	CSC_322.
	A PARENT SPAWNS 10 CHILDREN AND THE PARENT CAN COMMINUCATE TO ANY CHILD AND A CHILD CAN COMMUNNICATE WITH THE PARENT.
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
//#include <string.h>

int main(void)
{
	// declare variables.
	int n = 10; // number of processes.
	int fd_p2c[2]; // file descriptors for pipe to be used by parent 2 children.
	int fd_c2p[2]; // file descriptors for pipe to be used by child to parent.
	__pid_t p; // variable to hold fork function reply.
	__pid_t processes[10]; // hold process IDs
	
	// instantiate pipes
	if(pipe(fd_p2c) == -1){
		fprintf(stderr, "Pipe failed!\n");
	}
	if(pipe(fd_c2p) == -1){
		fprintf(stderr, "Pipe failed!\n");
	}

	// print parent process Id.
	printf("I'm the parent and my pid is: %d\n", getpid());

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

			//close(fd_p2c[1]); // close writing end of pipe.
			// print child process.
			printf("\nChild process Id is %d and parent ID is %d \n", getpid(), getppid());

        	char read_str[100]; // Read data from pipes.
        	read(fd_p2c[0], read_str, 4 * sizeof(read_str)); // read function.
        	//close(fd_p2c[0]); // close reading end of the pipe.
        	// print message from parent.
        	printf("The text from parent process is \'%s\' \n", read_str);

        	// create data to be sent to parent.
        	char send_data[100];
        	sprintf(send_data, "My process is %d and the square of the loop counter is %d \n", getpid(), i*i);

        	// child process send data to parent.
        	write(fd_c2p[1], send_data, 4 * sizeof(send_data));
        	//(fd_c2p[0]); // close read side.
        	//close(fd_c2p[1]); // close write side.
        	

        	_exit(0);//exit the child process to prevent further forking.

		} else {
			// parent process.
			//close(fd_p2c[0]); // close reading end of pipes.
			char write_str[100] = "Hello child what is your ID?";
			char read_data[100];
			// randomize from 1 - 100.
			
			// write data to pipe 0-9.
			write(fd_p2c[1], write_str, 4 * sizeof(write_str));

			// read from child processes. 
			read(fd_c2p[0], read_data, 4 * sizeof(read_data));
			printf("Child wrote: %s\n", read_data);
			//close(fd_c2p[0]); // close pipe.
			//close(fd_p2c[1]); // close pipe after reading from them.


		}

	}
	// parent cheking for termination of children.
	for (int i = 0; i < n; ++i)
	{
		int status;
		waitpid(processes[i], &status, 0);
		printf("Process %d exited with return code %d\n", processes[i], WEXITSTATUS(status));
	}

	// close both pipes.
	close(fd_c2p[0]);
	close(fd_c2p[1]);
	close(fd_p2c[0]);
	close(fd_p2c[1]);

	// exit program.
	return 0;
}