#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8888

int main(int argc, char const *argv[])
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int circulantmatrix[100];
    int opt = 1;
    int addrlen = sizeof(address);
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address,
             sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                             (socklen_t *)&addrlen)) < 0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    int array_size, c, r, buffer[100];
    c = read(new_socket, &array_size, sizeof(array_size));
    r = read(new_socket, &buffer, sizeof(buffer));
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

    send(new_socket, circulantmatrix, 100, 0);
    close(server_fd);
    printf("message sent\n");
    return 0;
}
