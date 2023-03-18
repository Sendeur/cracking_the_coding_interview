// String Rotation: Assume you have a method isSubstring that checks if one word is a substring of another.
// Given two strings, s1 and s2, write code to check if s2 is a rotation of s1 using only one call to isSubstring.
// e.g. "waterbottle" is a rotation of "erbottlewat"

#include <iostream>

#include <string>
#include <map>


// Check if s2 is rotation of s1.
bool IsRotation(const std::string& s1, const std::string& s2) {
  std::string ds1 = s1 + s1;
  return ds1.find(s2) != std::string::npos;
}

bool test_0() {
  return IsRotation("", "");
}

bool test_1() {
  return IsRotation("waterbottle", "erbottlewat");
}

bool test_2() {
  return !IsRotation("rbottle", "erbottlewat");
}

bool test_3() {
  return !IsRotation("waterboettl", "erbottlewat");
}

void run_tests() {
  std::map<std::string, bool(*)()> tests{
    { "Test 0", test_0 },
    { "Test 1", test_1 },
    { "Test 2", test_2 },
    { "Test 3", test_3 },
  };

  for (auto&[test, testfunc] : tests)
    if (testfunc())
      std::cout << test << " has PASSED!" << std::endl;
    else
      std::cout << test << " has FAILED!" << std::endl;
}

int main() {
  run_tests();
  return 0;
}
