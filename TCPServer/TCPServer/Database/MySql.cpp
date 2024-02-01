#include "MySql.h"

#include <jdbc/cppconn/driver.h>
#include <jdbc/cppconn/connection.h>
#include <jdbc/cppconn/statement.h>
#include "../Models/User.h"

#pragma comment(lib, "debug/mysqlcppconn")

MySql::MySql() : _connection(nullptr), _statement(nullptr), _isConnected(false), _isSetSchema(false),
                 _isCreatedStatement(false)
{
    _driver = get_driver_instance();
}

void MySql::Connect(const sql::SQLString& hostName, const sql::SQLString& userName, const sql::SQLString& password)
{
    _connection = _driver->connect(hostName, userName, password);
    if (_connection == nullptr)
    {
        _isConnected = false;
        throw GetException("Connection fail.");
    }
    _isConnected = true;
}

void MySql::SetSchema(const sql::SQLString& catalog)
{
    if (!_isConnected)
    {
        _isSetSchema = false;
        throw GetException("Connect first before set schema.");
    }
    _connection->setSchema(catalog);
    if (_connection->getSchema() != catalog)
    {
        _isSetSchema = false;
        throw GetException("Set schema fail.");
    }
    _isSetSchema = true;
}

void MySql::CreateStatement()
{
    if(!_isSetSchema)
    {
        _isCreatedStatement = false;
        throw GetException("Set schema first before create statement");
    }
    _statement = _connection->createStatement();
    if (_statement == nullptr)
    {
        _isCreatedStatement = false;
        throw GetException("Create statement fail.");
    }
    _isCreatedStatement = true;
}

User MySql::FindUser(const sql::SQLString& id) const
{
    constexpr char queryFormat[] = "select * from `user` where `id` = \"%s\"";
    const size_t queryLength = strlen(queryFormat) + id.length() + 1;
    char* query = new char[queryLength];
    const int result = sprintf_s(query, queryLength, queryFormat, id.c_str());
    if (result == -1)
    {
        throw GetException("Make Query fail.");
    }
    sql::ResultSet* resultSet = _statement->executeQuery(query);
    User user = {};
    for (;resultSet->next();)
    {
        sql::SQLString resultId = resultSet->getString("id");
        sql::SQLString resultPassword = resultSet->getString("password");
        sql::SQLString resultNickname = resultSet->getString("nickname");
        
        strcpy_s(user.Id, sizeof(user.Id), resultId.c_str());
        strcpy_s(user.Password, sizeof(user.Password), resultPassword.c_str());
        strcpy_s(user.Nickname, sizeof(user.Nickname), resultNickname.c_str());
    }
    if (strlen(user.Id) == 0)
    {
        throw GetException("User id is wrong");
    }
    if (user.Id != id)
    {
        throw GetException("Found user is difference");
    }
    
    delete[] query;
    return user;
}

std::exception MySql::GetException(const char* message)
{
    return std::exception(message);
}
