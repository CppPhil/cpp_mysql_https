#include <cstdint>
#include <cstdlib>

#include <iostream>
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
  const std::string connectionString{
    "host=127.0.0.1;user=root;password=letmein;db=cpp_db;compress=true;auto-"
    "reconnect="
    "true"};
  Poco::Data::Session session{Poco::Data::SessionFactory::instance().create(
    Poco::Data::MySQL::Connector::KEY, connectionString)};

  if (!session.isConnected()) {
    std::cerr << "session is not connected!\n";
    return EXIT_FAILURE;
  }

  if (!session.isGood()) {
    std::cerr << "session is bad!\n";
    return EXIT_FAILURE;
  }

  try {
    Customer              customer{1, "Peter Smith"};
    Poco::Data::Statement insertStatement{session};
    using namespace Poco::Data::Keywords;
    insertStatement << "INSERT INTO customer VALUES(?, ?)", use(customer.id),
      use(customer.name);
    const std::size_t rowsAffected{insertStatement.execute()};
    std::cout << "rowsAffected: " << rowsAffected << '\n';

    if (!insertStatement.done()) {
      std::cerr << "stament isn't done.\n";
      return EXIT_FAILURE;
    }
  }
  catch (const Poco::Exception& exception) {
    std::cerr << "Caught exception: " << exception.displayText() << '\n';
    return EXIT_FAILURE;
  }

  session.commit();
  session.close();
  return EXIT_SUCCESS;
}
