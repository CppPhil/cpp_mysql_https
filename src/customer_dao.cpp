#include <atomic>

#include "customer_dao.hpp"

namespace db {
CustomerDAO::CustomerDAO(Poco::Data::Session& session) : m_session{session}
{
}

std::optional<Customer> CustomerDAO::createCustomer(std::string name)
{
  const std::uint64_t id{nextId()};
  Customer            customer{id, std::move(name)};
  using namespace Poco::Data::Keywords;
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

std::uint64_t CustomerDAO::nextId()
{
  static std::atomic<std::uint64_t> id{1};
  return id++;
}
} // namespace db
