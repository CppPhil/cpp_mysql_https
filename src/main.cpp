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

#if 0
  // insert into database
  try {
    Customer              customer{1, "Peter Smith"};
    Poco::Data::Statement insertStatement{session};
    insertStatement << "INSERT INTO customer VALUES(?, ?)", use(customer.id),
      use(customer.name);
    const std::size_t rowsAffected{insertStatement.execute()};
    std::cout << "rowsAffected: " << rowsAffected << '\n';

    if (!insertStatement.done()) {
      std::cerr << "statement isn't done.\n";
      return EXIT_FAILURE;
    }
  }
  catch (const Poco::Exception& exception) {
    std::cerr << "Caught exception: " << exception.displayText() << '\n';
    return EXIT_FAILURE;
  }
#endif

#if 0
 // select
  try {
    Customer              customer{1, ""};
    Poco::Data::Statement selectStatement{session};
    using namespace Poco::Data::Keywords;
    selectStatement << "SELECT name FROM customer WHERE id=?",
      into(customer.name), use(customer.id);
    // range(0, 1); // iterate over result set one row at a time
    const std::size_t rowsAffected{selectStatement.execute()};
    std::cout << "rowsAffected: " << rowsAffected << '\n';

    if (!selectStatement.done()) {
      std::cerr << "statement isn't done.\n";
      return EXIT_FAILURE;
    }
  }
  catch (const Poco::Exception& exception) {
    std::cerr << "Caught exception: " << exception.displayText() << '\n';
    return EXIT_FAILURE;
  }
#endif

#if 0
  // update
  try {
    Customer              customer{1, "John Smith"};
    Poco::Data::Statement updateStatement{session};
    using namespace Poco::Data::Keywords;
    updateStatement << "UPDATE customer SET name=? WHERE id=?",
      use(customer.name), use(customer.id);
    const std::size_t rowsAffected{updateStatement.execute()};
    std::cout << "rowsAffected: " << rowsAffected << '\n';

    if (!updateStatement.done()) {
      std::cerr << "statement isn't done.\n";
      return EXIT_FAILURE;
    }
  }
  catch (const Poco::Exception& exception) {
    std::cerr << "Caught exception: " << exception.displayText() << '\n';
    return EXIT_FAILURE;
  }
#endif

#if 0
  // Delete
  try {
    Poco::Data::Statement deleteStatement{session};
    using namespace Poco::Data::Keywords;
    int id{1};
    deleteStatement << "DELETE FROM customer where id=?", use(id);
    const std::size_t rowsAffected{deleteStatement.execute()};
    std::cout << "rowsAffected: " << rowsAffected << '\n';

    if (!deleteStatement.done()) {
      std::cerr << "statement isn't done.\n";
      return EXIT_FAILURE;
    }
  }
  catch (const Poco::Exception& exception) {
    std::cerr << "Caught exception: " << exception.displayText() << '\n';
    return EXIT_FAILURE;
  }
#endif 

  session.commit();
  session.close();
  return EXIT_SUCCESS;
}
