#include "iperfer_server.h"

#define BACKLOG   5
#define MAXDATASIZE 1000

iperfer_server::iperfer_server(int port_)
{
    this->port = port_;
    this->numbytes = 0;
    this->new_fd = -1;
}

void iperfer_server::creat_sockets()
{
    string content, filename, temp;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        throw("socket create failed");
        exit(1);
    }
    server_addr.sin_family = AF_INET; // host byte order
    server_addr.sin_port = htons(port); // short, network byte order
    server_addr.sin_addr.s_addr = INADDR_ANY; // automatically fill with my IP
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1) {
        throw("socket bind failed");
        exit(1);
    }
    if (listen(sockfd, BACKLOG) == -1) {
        throw("socket listen failed");
        exit(1);
    }

}
void iperfer_server::run()
{
    //time is the duration in seconds for which data should be generated
    double seconds, rate, bandwidth, MB;
    char buf[MAXDATASIZE];
    int server_recv = 1, packet_size = 0;
    sin_size = sizeof(sockaddr_in);
    new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
    chrono::steady_clock::time_point start = chrono::steady_clock::now();
    if (new_fd == -1) {
        throw("socket accept failed");
    }
    memset(buf, 0, MAXDATASIZE);
    while ((server_recv = recv(new_fd, buf, MAXDATASIZE, 0)) != 0)
    {
        if (server_recv == -1) 
        {
            throw("socket receive failed");
        }
        packet_size += server_recv;
        if (packet_size % 1000 == 0)
        {
            numbytes += (packet_size / 1000);
            packet_size %= 1000;
        }
        memset(buf, 0, MAXDATASIZE);
        seconds = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start).count() / 1000000.0;
    }
    close(new_fd);
    new_fd = -1;
    MB = (double)numbytes / 1000.000;
    rate = MB * 8.0 / seconds;
    cout << "received = " <<numbytes << " KB, rate = " << fixed << rate  << " Mbps" << endl;
    numbytes = 0;
    close(sockfd);
}