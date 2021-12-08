#include "iperfer_client.h"
iperfer_client::iperfer_client(string host_, int port_, int times_)
{
    this->host = host_to_ip(host_);
    this->port = port_;
    this->timer = times_;
    this->times = times_;
    this->numbytes = 0;
}

void iperfer_client::creat_sockets()
{
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        throw("socket create failed");
        exit(1);
    }
    server_addr.sin_family = AF_INET; // host byte order
    server_addr.sin_port = htons(port); // short, network byte order
    server_addr.sin_addr.s_addr = inet_addr(this->host.c_str());
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1) {
        throw("socket connect failed");
        return;
    }
}

void iperfer_client::generate_chunks()
{
    char buf[MAXDATASIZE];
    memset(buf, 0, MAXDATASIZE);
    int state;
    state = send(sockfd, buf, MAXDATASIZE, 0);
    if (state == -1)
    {
        throw("socket send message failed");
    }
    else
        numbytes += 1;
}

void iperfer_client::run()
{
    //time is the duration in seconds for which data should be generated
    double seconds;
    chrono::steady_clock::time_point start = chrono::steady_clock::now();
    while (timer > 0)
    {
        generate_chunks();
        seconds = chrono::duration_cast<chrono::microseconds>(chrono::steady_clock::now() - start).count() / 1000000.0;
        if (seconds >= timer)
        {
            timer = 0;
        }
    }
    double MB = double(numbytes) / 1000, rate = MB * 8 / seconds;
    cout << "sent = " << numbytes << " KB, rate = " << fixed  << rate  << " Mbps" << endl;
    close(sockfd);
}

string iperfer_client::host_to_ip(string host_)
{
    int ret = 0;
    char error[1000] = {0};
    char host_ip[1024] = {0};
    if (host_ == "") {
        throw("invalid hostname or ip");
    }
    struct addrinfo hints;
    struct addrinfo *res, *res_p;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET; //ipv4
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_CANONNAME;
    hints.ai_protocol = 0;

    ret = getaddrinfo(host_.c_str(), NULL, &hints, &res);
    if (ret != 0) {
        sprintf(error, "%s", gai_strerror(ret));
        throw(error);
    }
    ret = getnameinfo(res->ai_addr, res->ai_addrlen, host_ip, sizeof(host), NULL, 0, NI_NUMERICHOST);
    if(ret != 0)
    {
        sprintf(error, "%s", gai_strerror(ret));
        throw(error);
    }
    freeaddrinfo(res);
    return host_ip;
}