// Stack Min: How would you design a stack which, in addition to push and pop,
// has a function min() which returns the minimum element?
// push(), pop() and min() should operate in O(1) time.
//
// Solution:
// - wrap 2 stacks
// - S1 keeps values
// - S2 keeps minimums, only add here IF value <= minSoFar
// pop value => S2.pop() if value == S2.top()

#include <iostream>
#include <stack>

class MinStack {
public:
  MinStack() {}

  void push(int val) {
    if (mins.empty())
      mins.push(val);
    else if (val <= mins.top())
      mins.push(val);

    values.push(val);
  }

  void pop() {
    if (mins.top() == values.top())
      mins.pop();

    values.pop();
  }

  int top() {
    return values.top();
  }

  int min() {
    return mins.top();
  }

  void print() {
    std::cout << "top=" << values.top() << " min=" << mins.top() << std::endl;
  }

  std::stack<int> values;
  std::stack<int> mins;
};

int main() {
  MinStack ms;

  ms.push(5);
  ms.print();

  ms.push(5);
  ms.print();

  ms.push(2);
  ms.print();

  ms.push(10);
  ms.print();

  ms.push(3);
  ms.print();

  ms.pop();
  ms.print();
  ms.pop();
  ms.print();
  ms.pop();
  ms.print();
  ms.pop();
  ms.print();

  return 0;
}
