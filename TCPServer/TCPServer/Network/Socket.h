#pragma once
#include <WinSock2.h>

#include "Packet.h"
#include "WinsockBase.h"

struct RequestLoginData;

class Socket : public WinsockBase
{
public:
    explicit Socket(SOCKET socket);
    ~Socket();
    char* Receive() const;
    char* Receive(size_t size) const;
    void StartReceive();
    void StopReceive();
private:
    SOCKET _socket;
    bool _isReceiving;

    void Send(const char* buffer, int length) const;
    void Login(const RequestLoginData& requestData) const;
    void CreateAccount(const RequestCreateAccountData& requestData) const;
    unsigned static WINAPI ReceiveThread(void* args);
};
