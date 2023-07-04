#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

namespace enc
{
class UDP_client
{
public:
    UDP_client(int serverPort);
    ~UDP_client();
    bool sendMessage(const char* message);
private:
    int sockfd;
    struct sockaddr_in serverAddr;
};
}//namespace enc