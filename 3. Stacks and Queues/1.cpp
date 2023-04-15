// Three in One: Describe how you could use a single array to implement three stacks.
//
// Solution:
// - capacity for each stack (S1, S2, S3), starting from 1
// - keep (left, right) per Sx to keep track of size(Sx)
// - Sx.push() => if size(Sx) > capacity(Sx), capacity(Sx) *= 2,
//    + reallocate array with size = capacity(S1) + capacity(S2) + capacity(S3)

#include <iostream>
#include <exception>
#include <vector>
#include <string>

class EmptyStackException : public std::exception {
public:
  EmptyStackException(int stack_index) : stack_index(stack_index) {}

  char* what() {
    char* str = "Sx is empty";
    str[1] = '0' + stack_index;
    return str;
  }

  int stack_index;
};

class ThreeStacks {
public:
  void s1_push(int elem) {
    if (s1_is_full())
      s1_grow();

    elems[s1_top_idx++] = elem;
    _s1_size++;
  }

  int s1_top() {
    return elems[s1_top_idx - 1];
  }

  void s1_pop() {
    if (s1_size() == 0)
      throw EmptyStackException{1};

    elems[--s1_top_idx] = -1;
    _s1_size--;
  }

  size_t s1_size() {
    return _s1_size;
  }

  bool s1_is_full() {
    return s1_size() == s1_capacity;
  }

  void s2_push(int elem) {
    if (s2_is_full())
      s2_grow();

    elems[s2_top_idx++] = elem;
    _s2_size++;
  }

  int s2_top() {
    return elems[s2_top_idx - 1];
  }

  void s2_pop() {
    if (s2_size() == 0)
      throw EmptyStackException{2};

    elems[--s2_top_idx] = -1;
    _s2_size--;
  }

  size_t s2_size() {
    return _s2_size;
  }

  bool s2_is_full() {
    return s2_size() == s2_capacity;
  }

  void s3_push(int elem) {
    if (s3_is_full())
      s3_grow();

    elems[s3_top_idx++] = elem;
    _s3_size++;
  }

  int s3_top() {
    return elems[s3_top_idx - 1];
  }

  void s3_pop() {
    if (s3_size() == 0)
      throw EmptyStackException{3};

    elems[--s3_top_idx] = -1;
    _s3_size--;
  }

  size_t s3_size() {
    return _s3_size;
  }

  bool s3_is_full() {
    return s3_size() == s3_capacity;
  }

//private:
  ThreeStacks() : elems(s1_capacity + s2_capacity + s3_capacity, -1) {

  }

  void s1_grow() {
    std::cout << "s1_grow()" << std::endl;
    std::vector<int> new_elems(2 * s1_capacity + s2_capacity + s3_capacity, -1);

    for (int i = 0; i < s1_size(); i++) {
      new_elems[i] = elems[i];
    }

    int j = 0;
    for (int i = 2 * s1_capacity; i < 2 * s1_capacity + s2_size(); i++, j++) {
      new_elems[i] = elems[j + s1_capacity];
    }

    j = 0;
    for (int i = 2 * s1_capacity + s2_capacity; i < 2 * s1_capacity + s2_capacity + s3_size(); i++, j++) {
      new_elems[i] = elems[j + s1_capacity + s2_capacity];
    }

    elems = std::move(new_elems);
    s2_top_idx += s1_capacity;
    s3_top_idx += s1_capacity;
    s1_capacity *= 2;
  }

  void s2_grow() {
    std::cout << "s2_grow()" << std::endl;
    std::vector<int> new_elems(s1_capacity + 2 * s2_capacity + s3_capacity, -1);

    for (int i = 0; i < s1_size(); i++) {
      new_elems[i] = elems[i];
    }

    int j = 0;
    for (int i = s1_capacity; i < s1_capacity + s2_size(); i++, j++) {
      new_elems[i] = elems[j + s1_capacity];
    }

    j = 0;
    for (int i = s1_capacity + 2 * s2_capacity; i < s1_capacity + 2 * s2_capacity + s3_size(); i++, j++) {
      new_elems[i] = elems[j + s1_capacity + s2_capacity];
    }

    elems = std::move(new_elems);
    s3_top_idx += s2_capacity;
    s2_capacity *= 2;
  }

  void s3_grow() {
    std::cout << "s3_grow()" << std::endl;
    std::vector<int> new_elems(s1_capacity + s2_capacity + 2 * s3_capacity, -1);

    for (int i = 0; i < s1_size(); i++) {
      new_elems[i] = elems[i];
    }

    int j = 0;
    for (int i = s1_capacity; i < s1_capacity + s2_size(); i++, j++) {
      new_elems[i] = elems[j + s1_capacity];
    }

    j = 0;
    for (int i = s1_capacity + s2_capacity; i < s1_capacity + s2_capacity + s3_size(); i++, j++) {
      new_elems[i] = elems[j + s1_capacity + s2_capacity];
    }

    elems = std::move(new_elems);
    s3_capacity *= 2;
  }

  // S1
  int s1_top_idx{0};
  size_t _s1_size{0};
  int s1_capacity{1};
  // S2
  int s2_top_idx{1};
  size_t _s2_size{0};
  int s2_capacity{1};
  // S3
  int s3_top_idx{2};
  size_t _s3_size{0};
  int s3_capacity{1};

  std::vector<int> elems;
};

std::ostream& operator<<(std::ostream& os, const ThreeStacks& ts) {
  os << "|S1 ";
  for (int i = 0; i < ts.s1_capacity; i++)
    os << ts.elems[i] << " ";
  os << "|";

  os << "|S2 ";
  for (int i = ts.s1_capacity; i < ts.s1_capacity + ts.s2_capacity; i++)
    os << ts.elems[i] << " ";
  os << "|";

  os << "|S3 ";
  for (int i = ts.s1_capacity + ts.s2_capacity; i < ts.s1_capacity + ts.s2_capacity + ts.s3_capacity; i++)
    os << ts.elems[i] << " ";
  os << "|";

  return os;
}

int main() {
  ThreeStacks ts;
  std::cout << ts << std::endl;

  ts.s1_push(1);
  ts.s1_push(2);
  ts.s1_pop();
  ts.s1_pop();
  std::cout << ts << std::endl;

  ts.s2_push(5);
  ts.s2_push(6);
  ts.s2_push(7);
  std::cout << ts << std::endl;

  ts.s3_push(10);
  ts.s3_push(11);
  ts.s3_push(12);
  std::cout << ts << std::endl;
 
  ts.s1_push(1);
  ts.s1_push(2);
  ts.s1_push(3);
  std::cout << ts << std::endl;

  std::cout << "S1 top = " << ts.s1_top() << std::endl;
  ts.s1_pop();
  std::cout << ts << std::endl;
 
  return 0;
}
