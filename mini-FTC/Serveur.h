#pragma once

#include <bits/stdc++.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

class Serveur
{
    private:
        int sockfd;
        struct sockaddr_in servaddr, cliaddr;
        socklen_t len;

    public:
        Serveur();
        void send(const char *buffer);
        int receive(char *buffer);
};
