#pragma once
#ifndef __TCPSERVER_H__
#define __TCPSERVER_H__

#include <exception>
#include <WinSock2.h>


class TcpServer
{
public:
    TcpServer();
    ~TcpServer();

    void Bind(unsigned short Port);

protected:
    static std::exception GetException(const char* Message);

private:
    SOCKET ListenSocket;

    bool Bound;
};

#endif