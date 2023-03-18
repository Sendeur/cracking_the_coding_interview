// Return Kth to Last: Implement an algorithm to find the K'th to last element of a singly linked list.

#include <iostream>

#include <forward_list>
#include <map>

int kth_to_last(const std::forward_list<int>& l, int k) {
  if (k < 0)
    return -1;

  auto slow = l.begin();
  auto fast = l.begin();

  // Advance fast by k elements
  while (k--) {
    std::advance(fast, 1);

    // k is bigger than the list size, return error code
    if (fast == l.end() && k > 0) {
      return -1;
    }
  }

  while (fast != l.end()) {
    std::advance(fast, 1);
    std::advance(slow, 1);
  }

  // slow now points to the k'th element from the last

  return *slow;
}

bool test_1() {
  return kth_to_last({1, 2, 3, 4, 5}, 1) == 5;
}

bool test_2() {
  return kth_to_last({1, 2, 3, 4, 5}, 2) == 4;
}

bool test_3() {
  return kth_to_last({1, 2, 3, 4, 5}, 3) == 3;
}

bool test_4() {
  return kth_to_last({1, 2, 3, 4, 5}, 4) == 2;
}

bool test_5() {
  return kth_to_last({1, 2, 3, 4, 5}, 5) == 1;
}

bool test_6() {
  return kth_to_last({1, 2, 3, 4, 5}, 6) == -1;
}

bool test_7() {
  return kth_to_last({1, 2, 3, 4, 5}, -1) == -1;
}

void run_tests() {
  std::map<std::string, bool(*)()> tests{
    { "Test 1", test_1 },
    { "Test 2", test_2 },
    { "Test 3", test_3 },
    { "Test 4", test_4 },
    { "Test 5", test_5 },
    { "Test 6", test_6 },
    { "Test 7", test_7 },
  };

  for (auto&[testname, testfunc] : tests) {
    if (testfunc())
      std::cout << testname << " passed SUCCESSFULLY." << std::endl;
    else
      std::cout << testname << " failed." << std::endl;
  }
}

int main() {
  run_tests();
  return 0;
}
