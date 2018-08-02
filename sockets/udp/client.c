
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 8080

int main(int argc, char *argv[])
{
    srand(time(NULL));
    int c;
    printf("Enter a number between 1 and 10:");
    scanf("%d", &c);
    int size = c * c;
    int matrix[100];
    for (int i = 0; i < c; i++)
    {
        for (int z = 0; z < c; z++)
        {
            int x = c * i + z;
            matrix[x] = rand() % 10;
        }
    }
    int sockfd;
    struct sockaddr_in servaddr;
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
    memset(&servaddr, 0, sizeof(servaddr));
    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;
    int n, len;
    int buffer[100];
    sendto(sockfd, &c, sizeof(c), 0, (const struct sockaddr *)&servaddr, sizeof(servaddr));
    sendto(sockfd, matrix, sizeof(matrix), 0, (const struct sockaddr *)&servaddr, sizeof(servaddr));
    recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&servaddr, &len);
    printf("do_circulant matrix: \n");
    for (int y = 0; y < c; y++)
    {
        int new_array_position = c * y;
        for (int i = 0; i < c; i++)
        {
            printf(" %d ", buffer[new_array_position + i]);
        }
        printf("\n");
    }

    close(sockfd);
}
