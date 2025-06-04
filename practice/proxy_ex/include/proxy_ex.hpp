#include <iostream>
#include <string>
#include <mutex>
#include <unordered_map>
#include <vector>
/**
 * Proxy design pattern:
 * Proxy design pattern is used when we want to add some functionality in between the client 
 * code and the final  functionality used by the client. For example in case of a database 
 * access. We might want to add some functionality in between the client and the database.
 * Its possible that we may want to add some security related checks in betweem. Also possible
 * that we may want to check the necessity of some operation before actually accessing the DB.
 * Also possible that we want to cache some data before the access to database, such that some
 * or most frequent operations need not go through to the DB and can be simply fulfilled by 
 * cached data. In that case we may want to create some proxy class which implements these kind
 * of operations. The proxy class follows the same interface as the database class so it looks
 * the same to client and client code need not change. Whereas internally, the proxy contains a 
 * reference to the original object and based on some logic decides whether a particular operation
 * needs to go through to the database.
 *  */

class Idatabase
{
    public:
        enum class operation
        {
            read,
            write
        };
        virtual std::string runQuery(std::string query) = 0;
        virtual std::string readFromDB(std::string query) = 0;
};

class database : public Idatabase
{
    public:
        std::string runQuery(std::string query);
        std::string readFromDB(std::string query);
};

class databaseProxy: public Idatabase
{
    private:
        std::unordered_map<std::string, std::string> readCache;
        bool checkCache(std::string query);
        std::string getFromCache(std::string query);
        database *DB;
    public:
        databaseProxy(database *DB): DB{DB}{}
        std::string runQuery(std::string query);
        std::string readFromDB(std::string query);
};