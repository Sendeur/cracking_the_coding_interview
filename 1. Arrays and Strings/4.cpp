// Palindrome Permutation: Given a string, write a function to check if it is a permutation
// of a palindrome. A palindrome is a word or phrase that is the same backwards and forwards.
// A permutation is a rearrangement of letters. The palindrome does not need to be limited to
// just dictionary words.
//
// EXAMPLE
// Input:   Tact Coa
// Output:  True (permutations: "taco cat", "atco cta", etc.)

#include <iostream>
#include <cassert>

#include <string>
#include <bitset>

bool is_permutation(const std::string& s) {
  // assume length(alphabet)=128
  std::bitset<128> freqs;

  for (int i = 0; i < s.length(); i++) {
    if (s[i] != ' ')
      freqs.flip(s[i]);
  }

  return freqs.count() <= 1;
}

int main() {
  assert(is_permutation("")==true);
  assert(is_permutation("taco cat")==true);
  assert(is_permutation("abdccdab")==true);
  assert(is_permutation("abc")==false);
  return 0;
}
