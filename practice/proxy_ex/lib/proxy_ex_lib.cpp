#include <iostream>
#include <string>
#include <cmath>
#include "proxy_ex.hpp"
#include <exception>
/**
 * proxy design pattern:
 * */
std::string database::runQuery(std::string query)
{
    std::cout<<"Running Query!! "<<query<<"\n";
    return "Running Query!!";
}
std::string database::readFromDB(std::string query)
{
    std::cout<<"Running Query to Read from DB\n";
    return runQuery(query);
}

bool databaseProxy::checkCache(std::string query)
{
    auto it = readCache.find(query);
    if (it != readCache.end())
    {
        std::cout<<"Found in cache!!\n";
        return true;
    }
    return false;
}

std::string databaseProxy::getFromCache(std::string query)
{
    auto it = readCache.find(query);
    if (it != readCache.end())
    {
        return it->second;
    }
    std::exception(std::invalid_argument("data not available"));
    return nullptr;
}

std::string databaseProxy::runQuery(std::string query)
{
    return DB->runQuery(query);
}

std::string databaseProxy::readFromDB(std::string query)
{
    bool exists = checkCache(query);
    if (exists)
    {
        try
        {
            return getFromCache(query);
        }
        catch(std::invalid_argument &e)
        {
            std::cout<<"received an exception: "<<e.what()<<"\n";
            return nullptr;
        }
    }
    else
    {
        auto result = DB->runQuery(query);
        std::cout<<"Storing in cache!!\n";
        readCache[query] = result;
        return result;
    }
}