// Palindrome: Implement a function to check if a linked list is a palindrome.

#include <forward_list>
#include <stack>
#include <map>
#include <string>
#include <functional>
#include <iostream>

int get_length(const std::forward_list<int> l) {
  int length{};

  for (auto it = l.begin(); it != l.end(); it++) {
    length++;
  }

  return length;
}

bool is_palindrome(const std::forward_list<int>& l) {
  std::forward_list<int>::const_iterator it = l.begin();
  std::stack<int> s;
  int n = get_length(l);
  int i{};

  // Add first n/2 elements into the stack.
  for (; i < n/2; i++, std::advance(it, 1)) {
    s.push(*it);
  }

  // Number of elems is mean, must skip the element in the middle.
  if (n % 2 != 0)
    std::advance(it, 1);

  // Compare remaining elements.
  for (; it != l.end(); it++) {
    // List too long.
    if (s.empty())
      return false;

    int elem = s.top();
    s.pop();

    if (elem != *it)
      return false;
  }

  return true;
}

int _get_kth_to_last(const std::forward_list<int>& l, int k) {
  auto it = l.begin();
  auto fast_it = l.begin();
  std::advance(fast_it, k+1);

  while (fast_it != l.end()) {
    std::advance(fast_it, 1);
    std::advance(it, 1);
  }

  return *it;
}

bool is_palindrome_memopt(const std::forward_list<int>& l) {
  int i{};

  for (auto it = l.begin(); it != l.end(); it++, i++) {
    int elem = _get_kth_to_last(l, i);

    if (*it != elem)
      return false;
  }

  return true;
}

bool test_0(bool(*is_palindrome)(const std::forward_list<int>&)) {
  return is_palindrome({}) == true;
}

bool test_1(bool(*is_palindrome)(const std::forward_list<int>&)) {
  return is_palindrome({1, 3, 3, 1}) == true;
}

bool test_2(bool(*is_palindrome)(const std::forward_list<int>&)) {
  return is_palindrome({1, 3, 5, 3, 1}) == true;
}

bool test_3(bool(*is_palindrome)(const std::forward_list<int>&)) {
  return is_palindrome({1, 3, 4, 5}) == false;
}

bool test_4(bool(*is_palindrome)(const std::forward_list<int>&)) {
  return is_palindrome({1, 3, 6, 4, 1}) == false;
}

bool run_tests() {
  std::map<std::string, std::function<bool()>> tests{
    {"[T] Test 0", std::bind(test_0, is_palindrome)},
    {"[T] Test 1", std::bind(test_1, is_palindrome)},
    {"[T] Test 2", std::bind(test_2, is_palindrome)},
    {"[T] Test 3", std::bind(test_3, is_palindrome)},
    {"[T] Test 4", std::bind(test_4, is_palindrome)},
    {"[S] Test 0", std::bind(test_0, is_palindrome_memopt)},
    {"[S] Test 1", std::bind(test_1, is_palindrome_memopt)},
    {"[S] Test 2", std::bind(test_2, is_palindrome_memopt)},
    {"[S] Test 3", std::bind(test_3, is_palindrome_memopt)},
    {"[S] Test 4", std::bind(test_4, is_palindrome_memopt)},
  };

  for (auto&[testname, testfunc] : tests) {
    if (testfunc())
      std::cout << testname << " passed successfully" << std::endl;
    else
      std::cout << testname << " failed" << std::endl;
  }

  return true;
}

int main() {
  (void)run_tests();
  return 0;
}
