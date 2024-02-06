#include "WinsockBase.h"

#include <cstdio>
#include <WinSock2.h>

std::exception WinsockBase::GetException(const char* message)
{
    const int errorCode = WSAGetLastError();
    const size_t length = 1 + sizeof(int) + strlen(message);
    char* exceptionMessage = new char[length];
    auto _ = sprintf_s(exceptionMessage,length,"[%d] %s", errorCode, message);
    std::exception exception(exceptionMessage);
    delete[] exceptionMessage;
    return exception;
}
