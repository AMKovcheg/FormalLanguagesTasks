#include "RegularExpression.h"
#include <iostream>

const size_t kInf = UINT64_MAX;

int main() {
  std::string alpha;
  size_t k;
  size_t l;
  std::cin >> alpha >> k >> l;
  auto answer = CountLen(alpha, k, l);
  if (answer == kInf) {
    std::cout << "INF";
  } else {
    std::cout << answer;
  }
}