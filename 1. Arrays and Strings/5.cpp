// One Away: There are three types of edits that can be performed on strings: insert a character,
// remove a character or replace a character. Given two strings, write a function to check if they
// are one edit (or zero edits) away.
//
// EXAMPLE
// pale, ple    -> true
// pales, pale  -> true
// pale, bale   -> true
// pale, bake   -> false

#include <string>
#include <cassert>

bool one_replace_away(const std::string& s1, const std::string& s2) {
  int len = s1.length();
  int i = 0;
  int j = 0;

  bool edit_found = false;
  while (i < len && j < len) {
    if (s1[i++] != s2[j++]) {
      // Found a second edit, return false.
      if (edit_found)
        return false;

      // We've found the one edit.
      edit_found = true;
    }
  }

  return edit_found;
}

bool one_rm_away(const std::string& s1, const std::string& s2) {
  int s1_len = s1.length();
  int s2_len = s2.length();
  int i = 0;
  int j = 0;

  bool rm_found = false;
  while (i < s1_len && j < s2_len) {
    // Current pair doesn't match.
    if (s1[i] != s2[j]) {
      // Already found a removal, return false;
      if (rm_found)
        return false;

      // Character removed from s1. Advance j (because s2 has one extra character).
      if (s1_len < s2_len)
        j++;
      // Character removed from s2. Advance i.
      else if (s1_len > s2_len)
        i++;

      rm_found = true;
    } else {
      // All good, continue matching.
      i++;
      j++;
    }
  }

  // Return true by default, because abs(s1_len-s2_len)==1 to begin with.
  return true;
}

bool one_edit_away(const std::string& s1, const std::string& s2) {
  int length_diff = s1.length() - s2.length();

  // Search for replace
  if (length_diff == 0) {
    return one_replace_away(s1, s2);
  // Search for removal
  } else if (std::abs(length_diff) == 1)  {
    return one_rm_away(s1, s2);
  }

  return false;
}

int main() {
  assert(one_edit_away("", "")==false);
  assert(one_edit_away("abcde", "abc")==false);
  assert(one_edit_away("abc", "abc")==false);
  assert(one_edit_away("pale", "ple")==true);
  assert(one_edit_away("pales", "pale")==true);
  assert(one_edit_away("pale", "bale")==true);
  assert(one_edit_away("pale", "bake")==false);
  return 0;
}
