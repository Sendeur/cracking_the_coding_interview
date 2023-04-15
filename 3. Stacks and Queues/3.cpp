// Stack of Plates: imagine a (literal) stack of plates. If the stack is too big, it might topple.

// In real life, we would start a new stack when the previous one exceeds some threshold. Implement
// a data structure SetOfStacks that mimics this real-life scenario. SetOfStacks should be composed
// of multiple stacks and should create a new stack if the previous one exceeds capacity.
// pop(), push() and top() should behave identically as if it were a single stack.
//
// Solution:
// - push => to last stack. if full, make new one (and make this one the last one)
// - pop => from last stack. if empty, remove it

// FOLLOW-UP: Implement a popAt(int idx) function to pop an element from the idx'th stack.

#include <iostream>

#include <vector>
#include <stack>
#include <exception>

class EmptyStackException : public std::exception {
public:
  const char* what() {
    return "Stack is empty";
  }
};


class StackOfPlates {
public:
  class NoStackException : public std::exception {
  public:
    const char* what() {
      return "Stack inexistent";
    }
  };

  StackOfPlates(size_t max_capacity) : max_capacity(max_capacity) {}

  void push(int val) {
    // No stacks yet.
    if (stacks.empty())
      stacks.push_back(std::stack<int>{});

    // Current stack is full.
    if (stacks.back().size() == max_capacity)
      stacks.push_back(std::stack<int>{});

    stacks.back().push(val);
  }

  int top() {
    if (is_empty())
      throw EmptyStackException{};

    return stacks.back().top();
  }

  void pop() {
    if (is_empty())
      throw EmptyStackException{};

    std::stack<int>& s = stacks.back();
    s.pop();

    // Also remove an empty stack. We should never have empty stacks.
    if (s.empty())
      stacks.pop_back();
  }

  void pop_from(int stack_idx) {
    if (stack_idx >= stacks.size())
      throw NoStackException{};

    std::stack<int>& s = stacks[stack_idx];
    s.pop();

    // Must move around elements from all subsequent stacks to fill the gap.
    for (int i = stack_idx; i < stacks.size() - 1; i++) {
      std::stack<int>& curr_s = stacks[i];
      std::stack<int>& next_s = stacks[i+1];
     
      // Transfer current stack contents to a temporary stack. 
      std::stack<int> tmp_s;
      while (!curr_s.empty()) {
        tmp_s.push(curr_s.top());
        curr_s.pop();
      }

      // Get top of next stack, place it at the bottom of current stack.
      curr_s.push(next_s.top());
      next_s.pop();

      // Spill temporary stack back into current stack.
      while (!tmp_s.empty()) {
        curr_s.push(tmp_s.top());
        tmp_s.pop();
      }
    }

    if (stacks.back().empty())
      stacks.pop_back();
  }

  bool is_empty() {
    return stacks.empty();
  }

  size_t max_capacity;
  std::vector<std::stack<int>> stacks;
};

std::ostream& operator<<(std::ostream& os, StackOfPlates sop) {
  std::vector<std::stack<int>> stacks = sop.stacks;
  for (int i = 0; i < stacks.size(); i++) {
    std::stack<int> s = stacks[i];
    os << "|S" << i;
    os << " size=" << s.size() << ";";
    while (!s.empty()) {
      os << " " << s.top();
      s.pop();
    }
    os << "|";
  }
  return os;
}

int main() {
  StackOfPlates sop{4};

  sop.push(1);
  sop.push(2);
  sop.push(3);
  sop.push(4);
  sop.push(5);
  sop.push(6);
  sop.push(7);
  sop.push(8);
  sop.push(9);
  sop.push(10);
  sop.push(11);
  std::cout << sop << std::endl;

  sop.pop_from(0);
  std::cout << sop << std::endl;


  return 0;
}
