// Partition: Write code to partition a linked list around a value of x, such that all nodes less than x
// come before all nodes greater than or equal to x. If x is contained in the list, the values of x only
// need to be after all elements less than x. The partition element x can appear anywhere in the right
// partition; it does not need to appear between the left and right partitions.
//
// EXAMPLE
// Input: 3 -> 5 -> 8 -> 5 -> 10 -> 2 -> 1 [partition=5]
// Output: 3 -> 1 -> 2 -> 10 -> 5 -> 5 -> 8

#include <forward_list>
#include <iostream>
#include <map>
#include <string>

std::forward_list<int> partition(const std::forward_list<int>& l, int partition_value) {
  std::forward_list<int> lpartition_list;
  std::forward_list<int> rpartition_list;
  std::forward_list<int>::iterator lit, rit;

  for (auto it = l.begin(); it != l.end(); it++) {
    if (*it >= partition_value) {
      // Add into right partition
      if (rpartition_list.empty()) {
        rpartition_list.push_front(*it);
        rit = rpartition_list.begin();

      } else {
        rpartition_list.insert_after(rit, *it);
        std::advance(rit, 1);
      }

    } else {
      // Add into left partition
      if (lpartition_list.empty()) {
        lpartition_list.push_front(*it);
        lit = lpartition_list.begin();

      } else {
        lpartition_list.insert_after(lit, *it);
        std::advance(lit, 1);
      }

    }
  }

  // Merge lpartition_list++rpartition_list
  for (auto it = rpartition_list.begin(); it != rpartition_list.end(); it++) {
    lpartition_list.insert_after(lit, *it);
    std::advance(lit, 1);
  }

  return lpartition_list;
}

bool operator==(const std::forward_list<int>& l1, const std::forward_list<int>& l2) {
  auto it1 = l1.begin();
  auto it2 = l2.begin();

  while (it1 != l1.end() and it2 != l2.end()) {
    if (*it1 != *it2)
      return false;

    std::advance(it1, 1);
    std::advance(it2, 1);
  }

  return it1 == l1.end() and it2 == l2.end();
}

std::ostream& operator<<(std::ostream& os, const std::forward_list<int>& l) {
  for (auto it = l.begin(); it != l.end(); it++) {
    os << *it << " " << std::endl;
  }

  return os;
}

bool test_0() {
  return partition(std::forward_list<int>{}, 5) == std::forward_list<int>{};
}

bool test_1() {
  // Input: 3 -> 5 -> 8 -> 5 -> 10 -> 2 -> 1 [partition=5]
  // Output: 3 -> 1 -> 2 -> 10 -> 5 -> 5 -> 8
  return partition(std::forward_list<int>{3, 5, 8, 5, 10, 2, 1}, 5) == std::forward_list<int>{3, 2, 1, 5, 8, 5, 10};
}

void run_tests() {
  std::map<std::string, bool(*)()> tests{
    {"Test 0", test_0},
    {"Test 1", test_1},
  };

  for (auto&[testName, testFunc] : tests) {
    if (testFunc())
      std::cout << testName << " passed successfully" << std::endl;
    else
      std::cout << testName << " failed" << std::endl;
  }
}

int main() {
  run_tests();
}
