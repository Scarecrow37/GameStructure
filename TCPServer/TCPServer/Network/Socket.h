#pragma once
#include <WinSock2.h>

#include "WinsockBase.h"

class Socket : public WinsockBase
{
public:
    explicit Socket(SOCKET socket);
    ~Socket();
    char* Receive() const;
    char* Receive(size_t size) const;
    void Send(const char* buffer, int length) const;
    void StartReceive();
    void StopReceive();
private:
    SOCKET _socket;
    bool _isReceiving;
    
    unsigned static WINAPI ReceiveThread(void* args);
};
