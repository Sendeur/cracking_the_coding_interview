// URLify: Write a method to replace all spaces in a string with "%20".
// You may assume that the string has sufficient space at the end to hold additional characters,
// and that you are given the "true" length of the string.
//
// EXAMPLE
// input:  "Mr John Smith    ", 13
// output: "Mr%20John%20Smith"

#include <iostream>
#include <string>
#include <cassert>

void URLify(std::string& s, int s_length) {
  int j = s.length()-1;

  for (int i = s_length-1; i >= 0; i--) {
    // Whitespace
    if (s[i] == ' ') {
      s[j--] = '0';
      s[j--] = '2';
      s[j--] = '%';
    // Not whitespace
    } else {
      s[j--] = s[i];
    }
  }

  std::cout << "URLify => " << s << std::endl;
}

using StringAndLen = std::pair<std::string, int>;

StringAndLen make_string(const std::string& s) {
  int len = s.length();
  std::string big_str = s;

  int ws_count = std::count(s.begin(), s.end(), ' ');
  big_str.resize(len + 2*ws_count);

  return StringAndLen{big_str, len};
}

int main() {
  // auto[...] declares the variables as well
  auto[s, len] = make_string("Mr John Smith");
  URLify(s, len);
  assert(s=="Mr%20John%20Smith");

  // std::tie(...) ties value to existing variables
  std::tie(s, len) = make_string("Mr           John");
  URLify(s, len);
  assert(s=="Mr%20%20%20%20%20%20%20%20%20%20%20John");

  std::tie(s, len) = make_string("");
  URLify(s, len);
  assert(s=="");

  std::tie(s, len) = make_string("    ");
  URLify(s, len);
  assert(s=="%20%20%20%20");

  return 0;
}
