// Check Permutation: Given two strings, write a method to decide if one is a permutation of the other.

#include <vector>
#include <string>
#include <cassert>

bool solution(const std::string s1, const std::string s2) {
  if (s1.length() != s2.length())
    return false;

  int n = s1.length();
  std::vector<int> freqs(128, 0);

  for (int i = 0; i < n; i++) {
    // Add frequency for first string
    freqs[s1[i]]++;
    // Subtract frequency for second string
    freqs[s2[i]]--;
  }

  for (int i = 0; i < 128; i++) {
    if (freqs[i] != 0)
      return false;
  }

  return true;
}

int main() {
  assert(solution("", "")==true);
  assert(solution("aaa", "aa")==false);
  assert(solution("abcd", "bcad")==true);
  assert(solution("axbda", "dabxa")==true);
  return 0;
}
