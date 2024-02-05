#include "Socket.h"

#include <iostream>

#include "TcpServer.h"
#include "../Thread/ThreadEx.h"

Socket::Socket(const SOCKET socket) : _socket(socket), _isReceiving(false)
{
}

Socket::~Socket()
{
    if (_isReceiving)
    {
        _isReceiving = false;
    }
    closesocket(_socket);
}

char* Socket::Receive() const
{
    // char* buffer = new char[1024];
    char buffer[1024] = { 0, };
    const int receiveSize = recv(_socket, buffer, 1024, 0);
    if (receiveSize < 0)
    {
        throw GetException("Receive Fail.");
    }
    if (receiveSize == 0)
    {
        throw GetException("Connection Close.");
    }
    for (int i = 0; buffer[i] != '\0'; ++i)
    {
        std::cout << buffer[i];
    }
    std::cout << std::endl;
    return buffer;
}

void Socket::Send()
{
}

void Socket::StartReceive()
{
    _isReceiving = true;
    const ThreadEx* thread = new ThreadEx(ReceiveThread);
    thread->Run(this);
}

void Socket::StopReceive()
{
    _isReceiving = false;
}

unsigned Socket::ReceiveThread(void* args)
{
    Socket* socket = (Socket*)args;
    while(socket->_isReceiving)
    {
        try
        {
            const char* receive = socket->Receive();
            std::string message(receive);
            std::cout << message << std::endl;
        }
        catch (std::exception& exception)
        {
            std::cout << exception.what() << std::endl;
            socket->StopReceive();
        }
    }
    return 0;
}
