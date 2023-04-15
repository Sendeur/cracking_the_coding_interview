// Queue via Stacks: implement a MyQueue data structure using 2 stacks.
//
// Solution:
// - push() => to S1
// - pop() => from S2. if S2 is empty, S1 => S2

#include <iostream>
#include <stack>

class MyQueue {
public:
  int front() {
    if (s2.empty())
      spill();

    return s2.top();
  }

  void pop() {
    if (s2.empty())
      spill();

    s2.pop();
  }

  void push(int val) {
    s1.push(val);
  }

  bool empty() {
    return s1.empty() && s2.empty();
  }
  
private:
  void spill() {
    while (!s1.empty()) {
      s2.push(s1.top());
      s1.pop();
    }
  }

  std::stack<int> s1;
  std::stack<int> s2;
};

std::ostream& operator<<(std::ostream& os, MyQueue que) {
  while (!que.empty()) {
    int val = que.front();
    que.pop();
    os << val << " ";
  }
  return os;
}

int main() {
  MyQueue que({1, 2});
  std::cout << que << std::endl;

  que.push(3);
  std::cout << que << std::endl;

  que.pop();
  std::cout << que << std::endl;
  return 0;
}
