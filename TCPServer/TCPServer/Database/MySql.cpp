#include "MySql.h"

#include <jdbc/cppconn/driver.h>
#include <jdbc/cppconn/connection.h>
#include <jdbc/cppconn/statement.h>
#include <jdbc/cppconn/prepared_statement.h>
#include "../Models/User.h"

#pragma comment(lib, "debug/mysqlcppconn")

MySql::MySql() : _connection(nullptr), _statement(nullptr), _findUserPreparedStatement(nullptr),
                 _createAccountPreparedStatement(nullptr), _isConnected(false),
                 _isSetSchema(false),
                 _isCreatedStatement(false)
{
    _driver = get_driver_instance();
}

MySql::MySql(const MySql& ref) : _connection(ref._connection), _statement(ref._statement),
                                 _findUserPreparedStatement(nullptr), _createAccountPreparedStatement(nullptr),
                                 _isConnected(ref._isConnected), _isSetSchema(ref._isSetSchema),
                                 _isCreatedStatement(ref._isCreatedStatement)
{
    _driver = ref._driver;
}

MySql& MySql::operator=(const MySql& ref)
{
    _connection = ref._connection;
    _statement = ref._statement;
    _findUserPreparedStatement = ref._findUserPreparedStatement;
    _createAccountPreparedStatement = ref._createAccountPreparedStatement;
    _isConnected = ref._isConnected;
    _isSetSchema = ref._isSetSchema;
    _isCreatedStatement = ref._isCreatedStatement;
    _driver = ref._driver;
    return *this;
}

MySql::~MySql()
{
    delete _findUserPreparedStatement;
    delete _createAccountPreparedStatement;
    delete _statement;
    _connection->close();
    delete _connection;
};

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

void MySql::InitializeStatements()
{
    if(!_isSetSchema)
    {
        _isCreatedStatement = false;
        throw GetException("Set schema first before create statement");
    }
    try
    {
        CreateStatement();
        CreateFindUserStatement();
        CreateCreateAccountStatement();
    }
    catch (...)
    {
        _isCreatedStatement = false;
        throw;
    }
    
    _isCreatedStatement = true;
}

void MySql::CreateStatement()
{
    _statement = _connection->createStatement();
    if (_statement == nullptr)
    {
        throw GetException("Create statement fail.");
    }
}

void MySql::CreateFindUserStatement()
{
    const sql::SQLString query("SELECT * FROM `user` WHERE `id` = ?");
    _findUserPreparedStatement = _connection->prepareStatement(query);
    if (_findUserPreparedStatement == nullptr)
    {
        throw GetException("Create prepared statement fail.");
    }
}

void MySql::CreateCreateAccountStatement()
{
    const sql::SQLString query("INSERT INTO `user` VALUES(?, ?, ?)");
    _createAccountPreparedStatement = _connection->prepareStatement(query);
    if (_createAccountPreparedStatement == nullptr)
    {
        throw GetException("Create create account statement fail.");
    }
}

User MySql::FindUser(const sql::SQLString& id) const
{
    _findUserPreparedStatement->setString(1, id);
    sql::ResultSet* resultSet = _findUserPreparedStatement->executeQuery();
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
    
    return user;
}

void MySql::CreateAccount(const User& user) const
{
    _createAccountPreparedStatement->setString(1, user.Id);
    _createAccountPreparedStatement->setString(2, user.Password);
    _createAccountPreparedStatement->setString(3, user.Nickname);
    _createAccountPreparedStatement->execute();
}

std::exception MySql::GetException(const char* message)
{
    return std::exception(message);
}
