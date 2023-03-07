// String Compression: Implement a method to perform basic string compression using the counts of repeated characters.
// For example, the string 'aabcccccaaa' would become 'a2b1c5a3'. If the 'compressed' string would not become smaller
// than the original array, your method should return the original string. You can assume the string has only uppercase
// and lowercase letters.

#include <string>
#include <cassert>

std::string compress(const std::string& s) {
  std::string out;

  char last_c = s[0];
  int count = 1;

  for (int i = 1; i < s.length(); i++) {
    if (s[i] != last_c) {
      out += last_c + std::to_string(count);
      last_c = s[i];
      count = 0;
    }

    count++;
  }

  // Emit what's left.
  if (count != 0)
    out += last_c + std::to_string(count);

  return out.length() < s.length() ? out : s;
}

int main() {
  assert(compress("aabcccccaaa")=="a2b1c5a3");
  assert(compress("aaaaaa")=="a6");
  assert(compress("abcd")=="abcd");
  assert(compress("aabb")=="aabb");
  return 0;
}
