#pragma once
#include <WinSock2.h>

class Socket
{
public:
    explicit Socket(SOCKET socket);
    ~Socket();
private:
    SOCKET _socket;
};
