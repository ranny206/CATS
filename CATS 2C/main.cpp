#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stack>
#include <functional>
#include <set>
#include <queue>
#include <string>
#include <memory>
#include <map>
#include <iomanip>
#include <sstream>
#include <cassert>

using std::string;
using std::cout;
using std::cin;
using std::vector;
using std::endl;

string class_id;

class Object {
 public:
  virtual std::string ToString() const = 0;
  virtual ~Object() {}
};

class Obj : public Object {
 public:
  Obj(const std::string &class_id) {
    class_id_ = class_id;
  }

  std::string ToString() const override {
    return class_id_;
  }

 private:
  std::string class_id_;
};

Object *apple_creator() {
  return new Obj("apple!");
}

Object *list_creator() {
  return new Obj("list");
}

Object *other_creator() {
  return new Obj("yet another identifier");
}

class Factory {
 public:

  Factory() {
    Register("apple!", &apple_creator);
    Register("list", &list_creator);
    Register("yet another identifier", &other_creator);
  }

  std::map<std::string, Object *> store;
  Object *Create(const std::string &class_id) {
    if (store.find((class_id)) != store.end()) {
      return new Obj(class_id);
    }
  }

  void Register(const std::string &class_id, Object *(*instance_creator)()) {
    if (store.find(class_id) == store.end()) {
      store[class_id] = instance_creator();
    }
  }

  ~Factory() {
    for (auto i = store.begin(); i != store.end(); i++) {
      delete(i->second);
    }
  }
};

class Smth : public Object {
 public:
  Smth(const std::string &class_id) {
    class_id_ = class_id;
  }

  std::string ToString() const override {
    return class_id_;
  }
 private:
  std::string class_id_;
};

Object *my_new_smth_() {
  return new Smth(class_id);
}

int main() {
  getline(cin, class_id);
  Factory factory;
  if (class_id != "apple!" && class_id != "list" && class_id != "yet another identifier") {
    factory.Register(class_id, my_new_smth_);
  }
  Object *smth_instance_ptr = factory.Create(class_id);
  cout << smth_instance_ptr->ToString() << endl;
  delete smth_instance_ptr;
}