#include "PacketManager.h"

#include <cstring>
#include <iostream>

Header PacketManager::BytesToHeader(const char* bytes)
{
    Header header;
    int pivot = 0;
    memcpy(&header.Size, &bytes[pivot], sizeof(header.Size));
    pivot += sizeof(header.Size);
    memcpy(&header.Type, &bytes[pivot], sizeof(header.Type));
    return header;
}

RequestLoginData PacketManager::BytesToRequestLoginData(const char* bytes)
{
    RequestLoginData data = {};
    int pivot = 0;
    const char* result = BytesToChar(&bytes[pivot], sizeof(data.Id));
    memcpy(&data.Id, result, sizeof(data.Id));
    pivot += sizeof(data.Id);
    result = BytesToChar(&bytes[pivot], sizeof(data.Password));
    memcpy(&data.Password, result, sizeof(data.Password));
    delete[] result;
    return data;
}

RequestCreateAccountData PacketManager::BytesToRequestCreateAccountData(const char* bytes)
{
    RequestCreateAccountData data = {};
    int pivot = 0;
    const char* result = BytesToChar(&bytes[pivot], sizeof(data.Id));
    memcpy(&data.Id, result, sizeof(data.Id));
    pivot += sizeof(data.Id);
    result = BytesToChar(&bytes[pivot], sizeof(data.Password));
    memcpy(&data.Password, result, sizeof(data.Password));
    pivot += sizeof(data.Password);
    result = BytesToChar(&bytes[pivot], sizeof(data.Nickname));
    memcpy(&data.Nickname, result, sizeof(data.Nickname));
    delete[] result;
    return data;
}

char* PacketManager::BytesToChar(const char* in, int count)
{
    char* result = new char[count];
    memset(result, 0, count);
    for (int i = 0; i < count; ++i)
    {
        if(in[i] == '\0') break;
        result[i] = (char)(in[i] + 0x1);
    }
    return result;
}
