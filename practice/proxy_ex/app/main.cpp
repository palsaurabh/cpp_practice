#include <iostream>
#include <string>
#include "proxy_ex.hpp"
   
int main() {
  database db;
  std::cout<<db.readFromDB("Query1")<<"\n";
  std::cout<<db.readFromDB("Query2")<<"\n";

  databaseProxy dbproxy(&db);
  std::cout<<dbproxy.readFromDB("Query1")<<"\n";
  std::cout<<dbproxy.readFromDB("Query1")<<"\n";

  return 0;
}
