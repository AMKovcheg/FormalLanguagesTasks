#include <stdexcept>
#include "RegularExpression.h"
#include <iostream>

const size_t kInf = UINT64_MAX;

RegularExpression::RegularExpression(const std::string& expression, size_t k) : k_(k) {
  root_ = Parse(expression);
}

std::shared_ptr<Node> RegularExpression::Parse(const std::string& expression) {
  std::stack<std::shared_ptr<Node>> expression_stack;
  std::shared_ptr<Node> cur_node;
  auto expression_size = expression.size();
  char cur_symb = ' ';
  for (size_t i = 0; i < expression_size; i++) {
    cur_symb = expression[i];
    cur_node = std::make_shared<Node>(Node(k_, cur_symb));
    if (cur_symb == '*') {
      if (expression_stack.empty()) {
        throw std::invalid_argument("Invalid regular expression");
      }
      cur_node->left_child_ = expression_stack.top();
      expression_stack.pop();
    } else if (cur_symb == '+' || cur_symb == '.') {
      if (expression_stack.size() < 2) {
        throw std::invalid_argument("Invalid regular expression");
      }
      cur_node->left_child_ = expression_stack.top();
      expression_stack.pop();
      cur_node->right_child_ = expression_stack.top();
      expression_stack.pop();
    } else if (cur_symb != 'a' && cur_symb != 'b' && cur_symb != 'c') {
      throw std::invalid_argument("Invalid regular expression");
    }
    expression_stack.push(cur_node);
    cur_node->ResetValues();
  }
  expression_stack.pop();
  if (!expression_stack.empty()) {
    throw std::invalid_argument("Invalid regular expression");
  }
  return cur_node;
}

size_t CountLen(const std::string& expression, size_t k, size_t l) {
  if (l >= k) {
    throw std::invalid_argument("l must be less, than k");
  }
  RegularExpression regular_expression(expression, k);
  auto root = regular_expression.GetRoot();
  auto min_len = root->GetMinLen();
  auto value = min_len[l];
  return value;
}