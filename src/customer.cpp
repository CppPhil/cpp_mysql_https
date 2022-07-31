#include <utility>

#include "customer.hpp"

namespace db {
Customer::Customer(std::uint64_t id, std::string name)
  : m_id{id}, m_name{std::move(name)}
{
}
} // namespace db
