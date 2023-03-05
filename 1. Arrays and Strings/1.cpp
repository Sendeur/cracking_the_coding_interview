// Is Unique: Implement an algorithm to determine if a string has all unique characters.

#include <string>
#include <bitset>

#include <iostream>
#include <cassert>

// Count frequencies in a bitset.
// If bit is already set, we return false.
bool solution(std::string& s) {
  // Assume ASCII alphabet
  std::bitset<128> freqs;

  for (int i = 0; i < s.length(); i++) {
    if (freqs.test(s[i]))
      return false;

    freqs.set(s[i]);
  }

  return true;
}

// What if you cannot use additional data structures?
/*
bool solution(std::string& s) {
  // Sort & check adjacent characters
  std::sort(s.begin(), s.end());

  for (int i = 1; i < s.length(); i++) {
    if (s[i] == s[i-1])
      return false;
  }

  return true;
}
*/

int main() {
  std::string s;

  s = "";
  assert(solution(s)==true);

  s = "abcdefgh";
  assert(solution(s)==true);

  s = "axywzaec";
  assert(solution(s)==false);
}
