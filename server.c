#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <ctype.h>

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[4096];
    if (argc < 3)
    {
        fprintf(stderr, "usage %s hostname port\n", argv[0]);
        exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL)
    {
        fprintf(stderr, "ERROR, no such host\n");
        exit(0);
    }
    bzero((char *)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR connecting");

    int num1;
    int num2;
    int ans;
    int choice;
    int matrix[25] = {0};
    FILE *fptr;
    fptr = fopen("seats.txt", "r");
    for (int i = 0; i < 25; i++)
    {
        fscanf(fptr, "%d", &matrix[i]);
    }
    fclose(fptr);
    int demand;
    bzero(buffer, 256);
    int query = read(sockfd, buffer, 256);
    printf("Server - %s \n ", buffer);

    scanf("%d", &demand);

    write(sockfd, &demand, sizeof(int));
    int reality;
    read(sockfd, &reality, sizeof(int));
    if (reality == 1)
    {
        // read string 1
        bzero(buffer, 256);
        read(sockfd, buffer, 255);
        printf("Server - %s \n", buffer);
        fflush(stdin);
        printf("\t");
        for (int i = 1; i < 26; i++)
        {
            printf("%d ", matrix[i - 1]);
            if (i % 5 == 0)
            {
                printf("\n");
                printf("\t");
            }
        }
        printf("\n");
        printf("server - enter the row no.- ");
        // enter choices
        for (int i = 0; i < demand; i++)
        {
            scanf("%d", &num1);
            write(sockfd, &num1, sizeof(int));
            bzero(buffer, 256);
            read(sockfd, buffer, 255);
            printf("server - %s \n", buffer);
            scanf("%d", &num2);
            write(sockfd, &num2, sizeof(int));
            bzero(buffer, 256);
            read(sockfd, buffer, 255);
            if (i != demand - 1)
            {
                printf("server - %s \n", buffer);
            }
        }
        close(sockfd);
    }
    else
    {
        bzero(buffer, 256);
        read(sockfd, buffer, 256);
        printf("Server - %s \n ", buffer);
        close(sockfd);
    }

    close(sockfd);
    return 0;
}
