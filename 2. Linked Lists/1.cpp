// Remove Dups: Write code to remove duplicates from an unsorted linked list.
// 
// Follow-up: what if NO space complexity is allowed?

#include <iostream>
#include <iterator>

#include <forward_list>
#include <set>
#include <map>

bool same_list(const std::forward_list<int>& l1, const std::forward_list<int>& l2) {
  auto p1 = l1.begin();
  auto p2 = l2.begin();

  while (p1 != l1.end() and p2 != l2.end()) {
    // elements differ
    if (*p1 != *p2)
      return false;

    p1++;
    p2++;
  }

  // no extra elements in neither of the two lists
  return p1 == l1.end() and p2 == l2.end();
}

std::ostream& operator<<(std::ostream& os, const std::forward_list<int>& l) {
  for (auto elem : l)
    os << elem << " ";
  os << std::endl;
  return os;
}

// Time-optimized version
void remove_dups_T(std::forward_list<int>& l) {
  std::set<int> values;
  auto curr = l.begin();
  auto prev = l.end();

  while (curr != l.end()) {
    if (values.find(*curr) == values.end()) {
      // OK, first time we've seen this
      values.insert(*curr);

      // just iterate
      prev = curr;
      curr++;

    } else {
      // duplicate, must remove
      l.erase_after(prev);

      curr = prev;
      std::advance(curr, 1);
    }
  }
}

// Memory-optimized version
void remove_dups_S(std::forward_list<int>& l) {
  auto curr = l.begin();

  while (curr != l.end()) {
    auto prev = curr;
    auto next = std::next(curr);

    // Erase all future occurences of *curr
    while (next != l.end()) {
      if (*curr == *next) {
        next = l.erase_after(prev);
      } else {
        prev = next;
        std::advance(next, 1);
      }
    }

    std::advance(curr, 1);
  }
}

bool test_0(void (*remove_dups)(std::forward_list<int>& l)) {
  std::forward_list<int> l{};
  std::forward_list<int> refl{};

  remove_dups(l);
  return same_list(l, refl);
}

bool test_1(void (*remove_dups)(std::forward_list<int>& l)) {
  std::forward_list<int> l{1, 1, 1, 1, 1, 1};
  std::forward_list<int> refl{1};

  remove_dups(l);
  return same_list(l, refl);
}

bool test_2(void (*remove_dups)(std::forward_list<int>& l)) {
  std::forward_list<int> l{1, 2, 3, 1, 3, 5};
  std::forward_list<int> refl{1, 2, 3, 5};

  remove_dups(l);
  return same_list(l, refl);
}

bool test_3(void (*remove_dups)(std::forward_list<int>& l)) {
  std::forward_list<int> l{1, 2, 3, 4};
  std::forward_list<int> refl{1, 2, 3, 4};

  remove_dups(l);
  return same_list(l, refl);
}

void run_tests_T() {
  std::map<std::string, std::function<bool()>> tests{
    { "[T] Test 0", std::bind(test_0, remove_dups_T) },
    { "[T] Test 1", std::bind(test_1, remove_dups_T) },
    { "[T] Test 2", std::bind(test_2, remove_dups_T) },
    { "[T] Test 3", std::bind(test_3, remove_dups_T) },
  };

  for (auto&[test, testfunc] : tests)
    if (testfunc())
      std::cout << test << " has passed SUCCESSFULLY." << std::endl;
    else
      std::cout << test << " has failed." << std::endl;
}

void run_tests_S() {
  std::map<std::string, std::function<bool()>> tests{
    { "[S] Test 0", std::bind(test_0, remove_dups_S) },
    { "[S] Test 1", std::bind(test_1, remove_dups_S) },
    { "[S] Test 2", std::bind(test_2, remove_dups_S) },
    { "[S] Test 3", std::bind(test_3, remove_dups_S) },
  };

  for (auto&[test, testfunc] : tests)
    if (testfunc())
      std::cout << test << " has passed SUCCESSFULLY." << std::endl;
    else
      std::cout << test << " has failed." << std::endl;
}

int main() {
  run_tests_T();
  run_tests_S();
  return 0;
}
