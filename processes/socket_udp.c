// KYANDE MICHAEL JOHN.
// P15 / 34906 / 2014.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>

int main()
{
    //variables.
    int sockets[2], child;
    char buf[1024];
    //create socket.
    if (socketpair(AF_UNIX, SOCK_DGRAM, 0, sockets) < 0)
    {
        //error handling
        fprintf(stderr, "failed to open sockets.");
        exit(1);
    }
    //fork to create a child
    if ((child = fork()) < 0)
        perror("fork");
    else if (child > 0)
    { /* This is the parent. */
        __pid_t processid = getpid();
        //char *message;
        //sprintf(message, "%d", processid);
        //close(sockets[0]);
        if (read(sockets[1], buf, 1024) < 0)
            perror("reading stream message");
        printf("Parent\'s message = %s\n", buf);
        if (write(sockets[1], &processid, sizeof(processid + 1)) < 0)
            perror("writing stream message");
        close(sockets[1]);
    }
    else
    { /* This is the child. */
        char message[] = "Send me your ID";
        close(sockets[1]);
        if (write(sockets[0], message, sizeof(message)) < 0)
            perror("writing stream message");
        if (read(sockets[0], buf, 1024) < 0)
            perror("reading stream message");
        printf("Child's message = %s\n", buf);
        close(sockets[0]);
    }
    return 0;
}