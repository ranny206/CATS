#pragma once

#include <memory>
#include "Test.hpp"

namespace smart_pointer {
class exception : std::exception {
  using base_class = std::exception;
  using base_class::base_class;
};

template<
    typename T,
    typename Allocator
>

class SmartPointer {
  ENABLE_CLASS_TESTS;

 public:
  using value_type = T;

  SmartPointer(value_type *p = nullptr) {
    if (p != nullptr) {
      this->core = new Core();
      core->data = p;
      core->counter = 1;
    } else {
      this->core = nullptr;
    }
  }

  SmartPointer(const SmartPointer &pointer) {
    this->core = pointer.core;
    if (pointer.core != nullptr) {
      core->counter++;
    }
  }

  SmartPointer(SmartPointer &&pointer) {
    this->core = pointer.core;
    pointer.core = nullptr;
  }

  SmartPointer &operator=(const SmartPointer &pointer) {
    Delete();
    this->core = pointer.core;
    if (pointer.core != nullptr) {
      core->counter++;
    }
    return *this;
  }

  SmartPointer &operator=(SmartPointer &&pointer) {
    Delete();
    this->core = pointer.core;
    pointer.core = nullptr;
    return *this;
  }

  SmartPointer &operator=(value_type *p) {
    Delete();
    if (p != nullptr) {
      this->core = new Core();
      core->data = p;
      core->counter = 1;
    } else {
      this->core = nullptr;
    }
    return *this;
  }

  void Delete() {
    if (core != nullptr) {
      core->counter--;
      if (core->counter == 0) {
        delete (core);
      }
    }
  }

  ~SmartPointer() {
    Delete();
  }

  value_type &operator*() {
    if (core != nullptr) {
      return *(core->data);
    } else {
      throw smart_pointer::exception();
    }
  }

  const value_type &operator*() const {
    if (core != nullptr) {
      return *(core->data);
    } else {
      throw smart_pointer::exception();
    }
  }

  value_type *operator->() const {
    if (core != nullptr) {
      return core->data;
    } else {
      return nullptr;
    }
  }

  value_type *get() const {
    if (core != nullptr) {
      return core->data;
    } else {
      return nullptr;
    }
  }

  operator bool() const {
    return core != nullptr;
  }

  template<typename U, typename AnotherAllocator>
  bool operator==(const SmartPointer<U, AnotherAllocator> &pointer) const {
    return static_cast<void *>(this->get()) == static_cast<void *>
    (pointer.get());
  }

  template<typename U, typename AnotherAllocator>
  bool operator!=(const SmartPointer<U, AnotherAllocator> &pointer) const {
    return static_cast<void *>(this->get()) != static_cast<void *>
    (pointer.get());
  }

  std::size_t count_owners() const {
    if (core != nullptr) {
      return core->counter;
    } else {
      return 0;
    }
  }

 private:
  class Core {
   public:
    size_t counter;
    value_type *data;

    ~Core() {
      Allocator allocator;
      allocator.deallocate(data, sizeof(value_type));
      data = nullptr;
    }
  };
  Core *core;
};
}  //namespace smart_pointer