#define _CRT_SECURE_NO_WARNINGS
#include "Socket.h"

#include <iostream>

#include "PacketManager.h"
#include "TcpServer.h"
#include "../Database/MySql.h"
#include "../Thread/ThreadEx.h"
#include "../Models/User.h"

std::string BytesToString(const char* In, int Count);

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
    char* buffer = new char[1024];
    const int receiveSize = recv(_socket, buffer, 1024, 0);
    if (receiveSize < 0)
    {
        throw GetException("Receive Fail.");
    }
    if (receiveSize == 0)
    {
        throw GetException("Connection Close.");
    }
    return buffer;
}

char* Socket::Receive(const size_t size) const
{
    char* buffer = new char[size];
    const int receiveSize = recv(_socket, buffer, (int)size, MSG_WAITALL);
    if (receiveSize < 0)
    {
        throw GetException("Receive Fail.");
    }
    if (receiveSize == 0)
    {
        throw GetException("Connection Close.");
    }
    return buffer;
}

void Socket::Send(const char* buffer, const int length) const
{
    int sentSize = 0;
    do
    {
        const int sendSize = send(_socket, &buffer[sentSize], length - sentSize, 0);
        if (sendSize < 0)
        {
            throw GetException("Receive Fail.");
        }
        if (sendSize == 0)
        {
            throw GetException("Connection Close.");
        }
        sentSize += sendSize;
    }
    while (sentSize < length);
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
            const char* receive = socket->Receive(sizeof(Header));
            const Header receiveHeader = PacketManager::BytesToHeader(receive);
            receive = socket->Receive(receiveHeader.Size);
            Header sendHeader;
            switch (receiveHeader.Type)
            {
            case RequestLogin:
                const RequestLoginData requestData = PacketManager::BytesToRequestLoginData(receive);
                User user;
                try{
                    user = MySql::GetInstance().FindUser(requestData.Id);
                } catch (...) {}
                ResponseLoginData responseData;
                responseData.IsSuccess = strcmp(requestData.Password, user.Password) == 0;
                if (responseData.IsSuccess)
                {
                    strcpy_s(responseData.Nickname, sizeof(user.Nickname), user.Nickname);
                }
                sendHeader = {sizeof(ResponseLoginData), ResponseLogin};
                socket->Send((char*)&sendHeader, sizeof(sendHeader));
                socket->Send((char*)&responseData, sizeof(responseData));
                break;
            default:
                throw GetException("Wrong header.");
            }
            delete[] receive;
        }
        catch (std::exception& exception)
        {
            std::cout << exception.what() << std::endl;
            socket->StopReceive();
        }
    }
    return 0;
}