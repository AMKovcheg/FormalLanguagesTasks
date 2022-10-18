#include <gtest/gtest.h>
#include "../Code/RegularExpression.h"

const size_t kInf = UINT64_MAX;

TEST(NodeConstructor, BasicTest) {
  EXPECT_NO_THROW(Node(1, 'a'));
}

TEST(NodeResetValues, OneChar) {
  Node node(2, 'a');
  EXPECT_NO_THROW(node.ResetValues());
  std::vector<size_t> test_vector = {kInf, 1};
  EXPECT_EQ(node.GetMinLen(), test_vector);
}

TEST(NodeResetPlus, PlusReset) {
  std::vector<size_t> min_len(6, kInf);
  std::vector<size_t> right = {kInf, 1, kInf, 3, 4, 5};
  std::vector<size_t> left = {12, kInf, 2, kInf, 10, kInf};
  Node node(1, 'a');
  node.PlusReset(min_len, left, right);
  std::vector<size_t> test_vector = {12, 1, 2, 3, 4, 5};
  EXPECT_EQ(min_len, test_vector);
}

TEST(NodeConcatenationReset, ConcatenationReset) {
  std::vector<size_t> min_len(6, kInf);
  std::vector<size_t> left = {kInf, 1, 8, kInf, kInf, kInf};
  std::vector<size_t> right = {6, kInf, kInf, 3, kInf, kInf};
  Node node(1, 'a');
  node.ConcatenationReset(min_len, left, right);
  std::vector<size_t> test_vector = {kInf, 7, 14, kInf, 4, 11};
  EXPECT_EQ(min_len, test_vector);
}

TEST(NodeStarReset, StarResetFirst) {
  std::vector<size_t> min_len(8, kInf);
  std::vector<size_t> left = {kInf, kInf, kInf, kInf, 4, kInf, 6, kInf};
  Node node(1, 'a');
  node.StarReset(min_len, left);
  std::vector<size_t> test_vector = {0, kInf, 10, kInf, 4, kInf, 6, kInf};
  EXPECT_EQ(min_len, test_vector);
}

TEST(NodeStarReset, StarResetSecond) {
  std::vector<size_t> min_len(7, kInf);
  std::vector<size_t> left = {kInf, kInf, 2, kInf, kInf, kInf, 6};
  Node node(1, 'a');
  node.StarReset(min_len, left);
  std::vector<size_t> test_vector = {0, 8, 2, 10, 4, 12, 6};
  EXPECT_EQ(min_len, test_vector);
}

TEST(NodeResetValues, TestPlusFirst) {
  auto first_node = std::make_shared<Node>(Node(3, 'a'));
  first_node->ResetValues();
  auto second_node = std::make_shared<Node>(Node(3, 'b'));
  second_node->ResetValues();
  Node parent_node(3, '+');
  parent_node.SetLeftChild(first_node);
  parent_node.SetRightChild(second_node);
  parent_node.ResetValues();
  std::vector<size_t> test_vector = {kInf, 1, kInf};
  EXPECT_EQ(parent_node.GetMinLen(), test_vector);
}

TEST(NodeResetValues, TestPlusSecond) {
  auto first_leave = std::make_shared<Node>(Node(4, 'a'));
  first_leave->ResetValues();
  auto second_leave = std::make_shared<Node>(Node(4, 'a'));
  second_leave->ResetValues();
  auto temp_parent = std::make_shared<Node>(Node(4, '.'));
  temp_parent->SetLeftChild(first_leave);
  temp_parent->SetRightChild(second_leave);
  temp_parent->ResetValues();
  auto third_leave = std::make_shared<Node>(Node(4, 'b'));
  third_leave->ResetValues();
  Node root(4, '+');
  root.SetLeftChild(temp_parent);
  root.SetRightChild(third_leave);
  root.ResetValues();
  std::vector<size_t> test_vector = {kInf, 1, 2, kInf};
  EXPECT_EQ(root.GetMinLen(), test_vector);
}

TEST(NodeResetValues, TestConcatenationFirst) {
  auto first_node = std::make_shared<Node>(Node(3, 'a'));
  first_node->ResetValues();
  auto second_node = std::make_shared<Node>(Node(3, 'b'));
  second_node->ResetValues();
  Node parent_node(3, '.');
  parent_node.SetLeftChild(first_node);
  parent_node.SetRightChild(second_node);
  parent_node.ResetValues();
  std::vector<size_t> test_vector = {kInf, kInf, 2};
  EXPECT_EQ(parent_node.GetMinLen(), test_vector);
}

TEST(NodeResetValues, TestConcatenationSecond) {
  auto first_leave = std::make_shared<Node>(Node(4, 'a'));
  first_leave->ResetValues();
  auto second_leave = std::make_shared<Node>(Node(4, 'a'));
  second_leave->ResetValues();
  auto temp_parent = std::make_shared<Node>(Node(4, '.'));
  temp_parent->SetLeftChild(first_leave);
  temp_parent->SetRightChild(second_leave);
  temp_parent->ResetValues();
  auto third_leave = std::make_shared<Node>(Node(4, 'b'));
  third_leave->ResetValues();
  auto other_temp_parent = std::make_shared<Node>(Node(4, '+'));
  other_temp_parent->SetLeftChild(temp_parent);
  other_temp_parent->SetRightChild(third_leave);
  other_temp_parent->ResetValues();
  auto fourth_leave = std::make_shared<Node>(Node(4, 'c'));
  fourth_leave->ResetValues();
  Node root(4, '.');
  root.SetLeftChild(other_temp_parent);
  root.SetRightChild(fourth_leave);
  root.ResetValues();
  std::vector<size_t> test_vector = {kInf, kInf, 2, 3};
  EXPECT_EQ(root.GetMinLen(), test_vector);
}

TEST(NodeResetValues, TestStarFirst) {
  auto node = std::make_shared<Node>(Node(3, 'a'));
  node->ResetValues();
  Node parent_node(3, '*');
  parent_node.SetLeftChild(node);
  parent_node.ResetValues();
  std::vector<size_t> test_vector = {0, 1, 2};
  EXPECT_EQ(parent_node.GetMinLen(), test_vector);
}

TEST(NodeResetValues, TestStarSecond) {
  auto first_leave = std::make_shared<Node>(Node(4, 'a'));
  first_leave->ResetValues();
  auto second_leave = std::make_shared<Node>(Node(4, 'a'));
  second_leave->ResetValues();
  auto temp_parent = std::make_shared<Node>(Node(4, '.'));
  temp_parent->SetLeftChild(first_leave);
  temp_parent->SetRightChild(second_leave);
  temp_parent->ResetValues();
  Node root(4, '*');
  root.SetLeftChild(temp_parent);
  root.ResetValues();
  std::vector<size_t> test_vector = {0, kInf, 2, kInf};
  EXPECT_EQ(root.GetMinLen(), test_vector);
}

TEST(RegularExpressionConstructor, CorrectBasicTest) {
  EXPECT_NO_THROW(RegularExpression regular_expression("ab+", 3));
}

TEST(RegularExpressionConstructor, IncorrectBasicTest) {
  EXPECT_ANY_THROW(RegularExpression regular_expression("a+", 2));
}

TEST(RegularExpressionConstructor, OrdinaryTest) {
  RegularExpression regular_expression("ab+c.", 3);
  auto root = regular_expression.GetRoot();
  auto min_len = root->GetMinLen();
  std::vector<size_t> test_vector = {kInf, kInf, 2};
  EXPECT_EQ(min_len, test_vector);
}

TEST(RegularExpressionConstructor, HardTest) {
  RegularExpression regular_expression("aa.b+*c.", 4);
  auto root = regular_expression.GetRoot();
  auto min_len = root->GetMinLen();
  std::vector<size_t> test_vector = {4, 1, 2, 3};
  EXPECT_EQ(min_len, test_vector);
}

TEST(CountLenTest, IncorrectInput) {
  size_t k = 3;
  size_t l = 5;
  std::string alpha = "ab+";
  EXPECT_ANY_THROW(CountLen(alpha, k, l));
  l = 2;
  alpha = "aaa+";
  EXPECT_ANY_THROW(CountLen(alpha, k, l));
}

TEST(CountLenTest, OrdinaryTest) {
  size_t k = 5;
  size_t l = 1;
  std::string alpha = "aa.bb.b.+*";
  EXPECT_EQ(CountLen(alpha, k, l), 6);
}