#pragma once
#include <WinSock2.h>

class Socket
{
public:
    Socket(SOCKET socket);
private:
    SOCKET _socket;
};
