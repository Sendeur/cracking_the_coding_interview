// Animal Shelter: An animal shelter, which holds only dogs and cats, operates on a FIFO basis.
// People must adopt:
// - the "oldest" animal (either Cat or Dog)
// - prefer Cat or Dog => they will get the last Animal of that type
// operations: enqueue, dequeueAny, dequeueDog, dequeueCat
// can use LinkedList
//
// Solution:
// - keep 2 queues: dogQueue, catQueue
// - hold (Animal, tag) as elements
// - dequeueAny => compare tags, pick the lowest tag animal

#include <iostream>

#include <queue>
#include <string>
#include <memory>

// for printing pointer address
#include <stdio.h>

struct Animal {
  std::string name;

  Animal(const std::string& name) : name(name) {}
  virtual ~Animal() { std::cout << "~Animal(" << name << ")" << std::endl; }

  virtual void make_sound() {
    std::cout << name << " ??" << std::endl;
  };
};

struct Dog : public Animal {
  Dog(const std::string& name) : Animal(name) {}
  ~Dog() { std::cout << "~Dog(" << name << ")" << std::endl; }

  void make_sound() {
    std::cout << name << " barks!" << std::endl;
  }
};

struct Cat : public Animal {
  Cat(const std::string& name) : Animal(name) {}
  ~Cat() { std::cout << "~Cat(" << name << ")" << std::endl; }

  void make_sound() {
    std::cout << name << " meows!" << std::endl;
  }
};

class AnimalShelter {
public:
  void enqueue(const Dog& d) {
    dog_queue.push({id++, std::make_unique<Dog>(std::move(d))});
  }

  void enqueue(const Cat& c) {
    cat_queue.push({id++, std::make_unique<Cat>(std::move(c))});
  }

  std::unique_ptr<Animal> dequeue_any() {
    if (cat_queue.empty())
      return dequeue_dog();
    else if (dog_queue.empty())
      return dequeue_cat();

    size_t id_cat, id_dog;
    std::tie(id_cat, std::ignore) = cat_queue.front();
    std::tie(id_dog, std::ignore) = dog_queue.front();
    if (id_cat < id_dog)
      return dequeue_cat();
    return dequeue_dog();
  }

  std::unique_ptr<Dog> dequeue_dog() {
    if (dog_queue.empty())
      return nullptr;

    auto&[_, dref] = dog_queue.front();
    std::unique_ptr<Dog> d = std::move(dref);
    dog_queue.pop();
    return d;
  }

  std::unique_ptr<Cat> dequeue_cat() {
    if (cat_queue.empty())
      return nullptr;

    auto&[_, cref] = cat_queue.front();
    std::unique_ptr<Cat> c = std::move(cref);
    cat_queue.pop();
    return c;
  }

private:
  std::queue<std::pair<int, std::unique_ptr<Dog>>> dog_queue;
  std::queue<std::pair<int, std::unique_ptr<Cat>>> cat_queue;
  int id{};
};

int main() {
  Cat cat{"Anca"};
  AnimalShelter as;
  as.enqueue(cat);
  as.enqueue(Dog{"Neacsu"});
  as.enqueue(Dog{"Prostea"});
  as.enqueue(Cat{"Andreea"});
  as.enqueue(Cat{"Bebe"});

  std::unique_ptr<Animal> a = as.dequeue_any();
  a->make_sound();
  std::unique_ptr<Dog> d = as.dequeue_dog();
  d->make_sound();
  std::unique_ptr<Cat> c = as.dequeue_cat();
  c->make_sound();
  
  return 0;
}
