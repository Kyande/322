// KYANDE MICHAEL JOHN.
// P15 / 34906 / 2014.
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

int main(int argc, char **argv)
{
    //variables
    char *hostname;
    struct hostent *address;

    //input hostname.
    printf("Please enter hostname: ");
    scanf("%s",hostname);
    //check hostname
    address = gethostbyname(hostname);

    if (address == NULL)
    {
        printf("can\'t resolve hostname\n");
    }
    else
    {
        printf("Domain = %s\n", address->h_name);
        printf("Address type = %d\n", address->h_addrtype);
        printf("I.P addresses\n");
        int i = 0;
        while (address->h_addr_list[i] != NULL)
        {
            printf("%d. %s \n",i+1 ,inet_ntoa(*(struct in_addr *)(address->h_addr_list[i])));
            i++;
        }
    }
}