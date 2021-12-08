#include <unistd.h>
#include <iostream>
#include <chrono>
#include <string>
#include <chrono>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <err.h>
#include <cstring>

#define MAXDATASIZE 1000

using namespace std;

class iperfer_server
{
    public:
        iperfer_server(){};
        iperfer_server(int port_);
        void creat_sockets();
        void run();
    private:
        unsigned long long int numbytes;
        struct sockaddr_in server_addr;
        struct sockaddr_in their_addr;
        socklen_t sin_size;
        int sockfd, new_fd, port;
};