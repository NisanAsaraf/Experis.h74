#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

namespace enc
{
class UDP_server
{
public:
    UDP_server(int port);
    ~UDP_server();
    bool sendMessage(const char* message, const struct sockaddr_in& clientAddr);
private:
    int sockfd;
    struct sockaddr_in serverAddr;
};
}//namespace enc