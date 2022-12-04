#pragma once

#include "Node.h"
#include <string>

class RegularExpression {
  std::string expression_;
  size_t k_;
  std::shared_ptr<Node> root_;
  std::shared_ptr<Node> Parse(const std::string& expression);

 public:
  RegularExpression(const std::string& expression, size_t k);
  auto GetRoot() {
    return root_;
  }
};

size_t CountLen(const std::string& expression, size_t k, size_t l);