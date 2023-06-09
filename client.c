#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <ctype.h>

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    char buffer[4096];
    struct sockaddr_in serv_addr, cli_addr;
    int n;
    if (argc < 2)
    {
        fprintf(stderr, "ERROR, no port provided\n");
        exit(1);
    }
    sockfd = socket(AF_INET, SOCK_STREAM, 0); // 0 - TCP
    if (sockfd < 0)
        error("ERROR opening socket");
    bzero((char *)&serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]); // argv[1] - contain the port number
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
        error("ERROR on binding");
    listen(sockfd, 5); // The number gives the maximum limit of client at same time
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd,
                       (struct sockaddr *)&cli_addr,
                       &clilen);
    if (newsockfd < 0)
    {
        error("ERROR on accept");
    }

    FILE *ptr;
    int arr[25];
    int available = 0;
    ptr = fopen("seats.txt", "r");
    for (int i = 0; i < 25; i++)
    {
        fscanf(ptr, "%d", &arr[i]);
    }
    fclose(ptr);
    for (int i = 0; i < 25; i++)
    {
        if (arr[i] == 0)
        {
            available++;
        }
    }
    int num1;
    int num2;
    int demand;
    int yes = 1;
    int no = 2;
    char str1[] = "There are 5 rows and 5 seats in each row \n \t 0 means seat available, 1 means seat occupied \n \t Type row number followed by seat number \n \t Enter row and seat no. :- \n";
    int query = write(newsockfd, "How many tickets do you want?", strlen("How many tickets do you want?"));
    if (query < 0)
    {
        error("Error writing lol");
    }
    read(newsockfd, &demand, sizeof(int));
    printf("CLIENT - I want %d seats \n", demand);
    printf("Available seats are %d \n", available);
    if (demand < available)
    {
        write(newsockfd, &yes, sizeof(int));
    }
    else
    {
        write(newsockfd, &no, sizeof(int));
    }
    if (demand < available)
    {
        write(newsockfd, &str1, sizeof(str1));
        fflush(stdin);
        for (int i = 0; i < demand; i++)
        {
            read(newsockfd, &num1, sizeof(int));
            printf("row number - %d \n", num1);
            write(newsockfd, "Now type the seat no.", sizeof("Now type the seat no."));
            read(newsockfd, &num2, sizeof(int));
            printf("seat no. - %d \n", num2);
            int pos = (5 * (num1 - 1) + num2) - 1;
            if (i == demand - 1 && arr[pos] != 1)
            {
                arr[pos] = 1;
                printf("Booked ticket %d ", i + 1);
            }
            else if (arr[pos] != 1)
            {
                write(newsockfd, "Type the row no.", sizeof("Type the row no."));
                arr[pos] = 1;
                printf("\n Booked ticket %d \n", i + 1);
            }
            else
            {
                write(newsockfd, "You have chosen a filled position, aborting", sizeof("You have chosen a filled position, aborting"));
                close(newsockfd);
                close(sockfd);
                break;
            }
        }
        FILE *optr;
        optr = fopen("seats.txt", "w");
        for (int i = 0; i < 25; i++)
        {
            fprintf(optr, "%d ", arr[i]);
        }
        fclose(optr);
        close(newsockfd);
        close(sockfd);
    }
    else
    {
        write(newsockfd, "sorry, tickets unavaiable", strlen("sorry, tickets unavaiable"));
        close(newsockfd);
        close(sockfd);
    }

    return 0;
}
