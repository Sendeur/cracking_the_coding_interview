// Sort Stack: Write a program to sort a stack such that the smallest items are on top.
// Can only use a temporary stack (but NOT an array or any other data structure).
// operations: push(), pop(), top(), isEmpty()
//
// Solution:
// - keep S2 sorted
// - elem = S1.top()
// - S2 => S1 until we find the right spot in S2 (S2.top() > elem)
// - S2.push(elem)
// - S1 => S2 back moved elements

#include <iostream>
#include <stack>

std::stack<int> sort_stack(std::stack<int> S1) {
  std::stack<int> S2;

  while (!S1.empty()) {
    // elem = S1.top()
    int elem = S1.top();
    S1.pop();

    // S2->S1 until we find proper insertion spot for elem
    //    S2.top() > elem || S2.empty()
    // keep $count of elements
    size_t elems_displaced{};
    while (!S2.empty() && S2.top() < elem) {
      int S2_top = S2.top();
      S2.pop();
      S1.push(S2_top);

      elems_displaced++;
    }

    // S2.push(elem)
    S2.push(elem);

    // S1->S2 $count times
    while (elems_displaced--) {
      int elem = S1.top();
      S1.pop();
      S2.push(elem);
    }
  }
 
  return S2;
}

std::ostream& operator<<(std::ostream& os, std::stack<int> s) {
  while (!s.empty()) {
    int val = s.top();
    os << val << " ";
    s.pop();
  }
  return os;
}

int main() {
  std::stack<int> s({5, 2, 4, 100, -100, 0, -1, 1});
  std::cout << sort_stack(s) << std::endl;
  return 0;
}
