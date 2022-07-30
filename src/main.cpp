#include <cstdint>

#include <string>

#include <Poco/Data/MySQL/Connector.h>
#include <Poco/Data/Session.h>
#include <Poco/Data/SessionFactory.h>

struct Customer {
  std::uint64_t id;
  std::string   name;
};

int main()
{
  Poco::Data::MySQL::Connector::registerConnector();
  const std::string connectionString{"host=127.0.0.1;user=root;password=letmein;compress=true;auto-reconnect=true"};
  Poco::Data::Session test{Poco::Data::SessionFactory::instance().create(Poco::Data::MySQL::Connector::KEY, connectionString)};

  
}
