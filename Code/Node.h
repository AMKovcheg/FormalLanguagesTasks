#pragma once

#include <memory>
#include <vector>
#include <stack>

class Node {
  std::shared_ptr<Node> right_child_;
  std::shared_ptr<Node> left_child_;
  std::vector<size_t> min_len_;
  char node_symbol_;
  friend class RegularExpression;

 public:
  auto GetMinLen() {
    return min_len_;
  }
  void ResetValues();
  void StarReset(std::vector<size_t>& min_len, const std::vector<size_t>& child_min_len);
  void ConcatenationReset(std::vector<size_t>& min_len, const std::vector<size_t>& left_min_len, const std::vector<size_t>& right_min_len);
  void PlusReset(std::vector<size_t>& min_len, const std::vector<size_t>& left_min_len, const std::vector<size_t>& right_min_len);
  Node(size_t k, char symbol);
  void SetLeftChild(std::shared_ptr<Node> left_child);
  void SetRightChild(std::shared_ptr<Node> right_child);
};