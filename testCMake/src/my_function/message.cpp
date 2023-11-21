#include "my_function/message.hpp"
#include <ostream>

std::ostream &Message::PrintObject(std::ostream &os) {
  os << "Message: ";
  os << message_;
  return os;
}