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

    void Initialize();
    void Bind(unsigned short Port);
    void Listen(int Backlog = 1);
    void Accept();

protected:
    static std::exception GetException(const char* Message);

private:
    SOCKET ListenSocket;

    bool Initialized;
    bool Bound;
    bool Listened;
};

#endif
