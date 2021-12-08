#include <iostream>
#include <string>
#include <cstring>
#include "iperfer_client.h"
#include "iperfer_server.h"

using namespace std;

int port_to_num(string port_str)
{
    int port_num;
    for (int i = 0; i < port_str.length(); i++)
    {
        if ((port_str[i] >= '0' && port_str[i] <= '9') == false)
            throw("port must be a number");
    }
    port_num = stoi(port_str);
    if ((port_num >= 1024 && port_num <= 65536) == false)
    {
        throw("port number must be in the range 1024 to 65535");
    }
    return port_num;
}

int main(int argc, char *argv[])
{
    try
    {
        if (argc < 4)
            throw("missing or additional arguments");
        else
        {
            if (argc == 4 && strcmp(argv[1],"-s") == 0 && strcmp(argv[2], "-p") == 0)
            {
                int port = port_to_num(argv[3]);
                iperfer_server serv(port);
                serv.creat_sockets();
                serv.run();
            }
            else if (argc == 8 && strcmp(argv[1], "-c") == 0)
            {
                string host;
                int port, times;
                for (int i = 2; i < argc; i++)
                {
                    if (strcmp(argv[i], "-h") == 0)
                    {
                        host = argv[i + 1];
                        i++;
                    }
                    else if (strcmp(argv[i], "-p") == 0)
                    {
                        port = port_to_num(argv[i + 1]);
                        i++;
                    }
                    else if (strcmp(argv[i], "-t") == 0)
                    {
                        times = stoi(argv[i + 1]);
                        i++;
                    }
                    else
                        throw("missing or additional arguments");
                }
                iperfer_client cli(host, port, times);
                cli.creat_sockets();
                cli.run();
            }
            else
                throw("missing or additional arguments");
        }
    }
    catch(char const* content)
    {
        cerr << "Error: " << content << endl;
    }
    return 0;
}