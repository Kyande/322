#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <math.h>

#define PORT 8080

int main(int argc, char *argv[])
{
    int sockfd;
    int buffer[100];
    int circulantmatrix[100];
    struct sockaddr_in servaddr, cliaddr;
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));
    // Filling server information
    servaddr.sin_family = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);
    // Bind the socket with the server address
    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    int array_size;
    int len, n, c;
    int x;
    //c = recvfrom(sockfd, x, 1, MSG_WAITALL, ( struct sockaddr *) &cliaddr,&len);
    recvfrom(sockfd, &array_size, sizeof(array_size), 0, (struct sockaddr *)&cliaddr, &len);
    int array_sizeC = array_size * array_size;
    n = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&cliaddr, &len);
    //first line of array
    for (int i = 0; i < array_size; i++)
    {
        circulantmatrix[i] = buffer[i];
    }

    for (int u = 1; u < array_size; u++)
    {
        //get array index position
        int new_array_position = array_size * u;
        int previous_index = u - 1;
        int previous_array_position = array_size * previous_index;

        for (int i = 0; i < array_size - 1; i++)
        {
            // let demodata [i]= newarray[i+1];

            circulantmatrix[new_array_position + i + 1] = circulantmatrix[previous_array_position + i];
        }
        circulantmatrix[new_array_position] = circulantmatrix[new_array_position - 1];
    }
    sendto(sockfd, circulantmatrix, sizeof(circulantmatrix), 0, (const struct sockaddr *)&cliaddr, len);
    printf("DONE!.\n");

    return 0;
}