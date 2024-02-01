#include "MySql.h"

#pragma comment(lib, "debug/mysqlcppconn")

MySql::MySql() : _connection(nullptr), _connected(false)
{
    _driver = get_driver_instance();
}

void MySql::Connect(const char* hostName, const char* userName, const char* password)
{
    _connection = _driver->connect(hostName, userName, password);
    if (_connection == nullptr)
    {
        _connected = false;
        throw GetException("Connection fail.");
    }
    else
    {
        _connected = true;
    }
}

std::exception MySql::GetException(const char* message)
{
    return std::exception(message);
}
