#pragma once
#ifndef __TCPSERVER_H__
#define __TCPSERVER_H__

#include <exception>
#include <WinSock2.h>

#include "Socket.h"
#include "WinsockBase.h"


class TcpServer : public WinsockBase
{
public:
    TcpServer();
    ~TcpServer();

    void Initialize();
    void Bind(unsigned short port);
    void Listen(int backlog = 1);
    Socket* Accept() const;
    void Start();
    void Stop();


private:
    SOCKET _listenSocket;

    bool _isInitialized;
    bool _isBound;
    bool _isListened;
    bool _isAccepting;
    
    unsigned static WINAPI AcceptThread(void* args);
};

#endif
