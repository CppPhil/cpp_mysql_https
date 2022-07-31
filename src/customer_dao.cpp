#include <atomic>

#include "customer_dao.hpp"

namespace db {
using namespace Poco::Data::Keywords;

CustomerDAO::CustomerDAO(Poco::Data::Session& session) : m_session{session}
{
}

std::optional<Customer> CustomerDAO::createCustomer(std::string name)
{
  try {
    const std::uint64_t   id{nextId()};
    Customer              customer{id, std::move(name)};
    Poco::Data::Statement insertStatement{m_session};
    insertStatement << "INSERT INTO customer VALUES(?, ?)", use(customer.m_id),
      use(customer.m_name);
    const std::size_t rowsAffected{insertStatement.execute()};

    if (rowsAffected == 0) {
      return std::nullopt;
    }

    if (!insertStatement.done()) {
      return std::nullopt;
    }

    return customer;
  }
  catch (const Poco::Exception& exception) {
    return std::nullopt;
  }
}

bool CustomerDAO::updateCustomer(Customer& customer, std::string newName)
{
  try {
    Poco::Data::Statement updateStatement{m_session};
    updateStatement << "UPDATE customer SET name=? WHERE id=?",
      use(customer.m_id), use(newName);
    const std::size_t rowsAffected{updateStatement.execute()};

    if (rowsAffected == 0) {
      return false;
    }

    if (!updateStatement.done()) {
      return false;
    }

    customer.m_name = std::move(newName);
    return true;
  }
  catch (const Poco::Exception& exception) {
    return false;
  }
}

std::uint64_t CustomerDAO::nextId()
{
  static std::atomic<std::uint64_t> id{1};
  return id++;
}
} // namespace db
