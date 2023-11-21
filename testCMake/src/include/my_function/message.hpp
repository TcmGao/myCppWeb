#ifndef FUNCTIONS_MESSAGE_H
#define FUNCTIONS_MESSAGE_H

#include <ostream>
#include <string>


class Message {
  public:
  Message(const std::string &m) : message_(m){}
  friend std::ostream &operator<<(std::ostream &os, Message &m) {
    return m.PrintObject(os);
  }

  private:
  std::string message_;
  std::ostream &PrintObject(std::ostream &os);
};

#endif