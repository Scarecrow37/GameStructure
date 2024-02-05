#pragma once
#include <exception>

class WinsockBase
{
protected:
    static std::exception GetException(const char* message);
};
