#pragma once
#include <cstdint>

#include <string>

namespace db {
class CustomerDAO;

class Customer {
public:
  friend class CustomerDAO;

private:
  Customer(std::uint64_t id, std::string name);

  std::uint64_t m_id;
  std::string   m_name;
};
} // namespace db
