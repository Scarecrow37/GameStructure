#include "Socket.h"

Socket::Socket(const SOCKET socket) : _socket(socket)
{
}

Socket::~Socket()
{
    closesocket(_socket);
}
