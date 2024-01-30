#pragma once
#ifndef __TCPSERVER_H__
#define __TCPSERVER_H__

#include <exception>
#include <WinSock2.h>

#include "Socket.h"


class TcpServer
{
public:
    TcpServer();
    ~TcpServer();

    void Initialize();
    void Bind(unsigned short port);
    void Listen(int backlog = 1);
    Socket* Accept();

protected:
    static std::exception GetException(const char* message);

private:
    SOCKET _listenSocket;

    bool _initialized;
    bool _bound;
    bool _listened;
};

#endif
