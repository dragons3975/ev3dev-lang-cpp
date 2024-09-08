#include "Serveur.h"

#define PORT 8080

Serveur::Serveur()
{
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 )
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
    
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));
    
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);
    
    if ( bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0 )
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    struct timeval tv;
    tv.tv_sec = 0;
    tv.tv_usec = 100000;
    if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) < 0)
    {
        perror("Set Timeout error");
    }

    len = sizeof(cliaddr);
}

void Serveur::send(const char *buffer)
{
    sendto(sockfd, buffer, buffer[0], MSG_CONFIRM, (const struct sockaddr *) &cliaddr, len);
}

int Serveur::receive(char *buffer)
{
    return recvfrom(sockfd, buffer, 1024, MSG_WAITALL, (struct sockaddr *) &cliaddr, &len);
}
