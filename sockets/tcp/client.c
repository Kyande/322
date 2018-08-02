#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <string.h>
#define PORT 8888

int main(int argc, char const *argv[])
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
            //printf("z=%d\n, x=%d\n",z,x);
            matrix[x] = rand() % 10;
        }
    }
    struct sockaddr_in address;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }
    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    send(sock, &c, sizeof(c), 0);
    send(sock, &matrix, sizeof(matrix), 0);
    int buffer[100];
    valread = recv(sock, &buffer, sizeof(buffer), 0);
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
    close(sock);
    return 0;
}
