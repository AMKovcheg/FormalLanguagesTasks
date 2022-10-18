#include "Node.h"
#include <algorithm>
#include <set>

const size_t kInf = UINT64_MAX;

Node::Node(size_t k, char symbol) : min_len_(k, kInf), node_symbol_(symbol) {
}

void Node::ResetValues() {
  if (node_symbol_ >= 'a' && node_symbol_ <= 'c') {
    min_len_[1] = 1;
    return;
  }
  if (node_symbol_ == '+') {
    PlusReset(min_len_, left_child_->min_len_, right_child_->min_len_);
    return;
  }
  if (node_symbol_ == '.') {
    ConcatenationReset(min_len_, left_child_->min_len_, right_child_->min_len_);
    return;
  }
  if (node_symbol_ == '*') {
    StarReset(min_len_, left_child_->min_len_);
    return;
  }
}

void Node::SetLeftChild(std::shared_ptr<Node> left_child) {
  left_child_ = left_child;
}

void Node::SetRightChild(std::shared_ptr<Node> right_child) {
  right_child_ = right_child;
}

void Node::StarReset(std::vector<size_t>& min_len, const std::vector<size_t>& child_min_len) {
  auto k = min_len.size();
  std::vector<size_t> new_residues;
  std::vector<size_t> cur_residues;
  std::set<size_t> all_residues;
  std::set<size_t> cur_all_residues;
  size_t idx;
  for (auto num : child_min_len) {
    if (num != kInf) {
      idx = num % k;
      new_residues.push_back(idx);
      min_len[idx] = std::min(min_len[idx], num);
    }
  }
  size_t temp_residue;
  while (new_residues.size() != 0) {
    cur_residues = new_residues;
    cur_all_residues = all_residues;
    new_residues.clear();
    for (auto cur_residue : cur_residues) {
      for (auto residue : cur_all_residues) {
        temp_residue = (cur_residue + residue) % k;
        if (all_residues.find(temp_residue) == all_residues.end()) {
          new_residues.push_back(temp_residue);
          all_residues.insert(temp_residue);
        }
        if (min_len[cur_residue] != kInf && min_len[residue] != kInf) {
          min_len[temp_residue] = std::min(min_len[temp_residue], min_len[cur_residue] + min_len[residue]);
        }
      }
      for (auto residue : cur_residues) {
        temp_residue = (cur_residue + residue) % k;
        if (all_residues.find(temp_residue) == all_residues.end()) {
          new_residues.push_back(temp_residue);
          all_residues.insert(temp_residue);
        }
        if (min_len[cur_residue] != kInf && min_len[residue] != kInf) {
          min_len[temp_residue] = std::min(min_len[temp_residue], min_len[cur_residue] + min_len[residue]);
        }
      }
    }
    for (auto residue : cur_residues) {
      all_residues.insert(residue);
    }
  }
  min_len[0] = 0;
}

void Node::PlusReset(std::vector<size_t>& min_len, const std::vector<size_t>& left_min_len, const std::vector<size_t>& right_min_len) {
  size_t min = kInf;
  auto k = min_len.size();
  for (size_t i = 0; i < k; i++) {
    min = std::min(right_min_len[i], left_min_len[i]);
    min_len[i] = std::min(min_len[i], min);
  }
}

void Node::ConcatenationReset(std::vector<size_t>& min_len, const std::vector<size_t>& left_min_len, const std::vector<size_t>& right_min_len) {
  auto k = min_len.size();
  size_t idx;
  for (size_t i = 0; i < k; i++) {
    for (size_t j = 0; j < k; j++) {
      idx = (i + j) % k;
      if (left_min_len[i] != kInf && right_min_len[j] != kInf) {
        min_len[idx] = std::min(min_len[idx], left_min_len[i] + right_min_len[j]);
      }
    }
  }
}