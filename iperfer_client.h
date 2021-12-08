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

class iperfer_client
{
    public:
        iperfer_client(){};
        iperfer_client(string host_, int port_, int times_);
        void creat_sockets();
        void generate_chunks();
        void run();
        string host_to_ip(string host_);
    private:
        unsigned long long int timer, numbytes, times;
        struct sockaddr_in server_addr;
        int sockfd, port;
        string host;

};