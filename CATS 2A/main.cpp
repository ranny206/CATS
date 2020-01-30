#include <iostream>
#include <vector>

class PageAllocator {
  const std::uint64_t page_size_;
  std::vector<void *> pages_;

 public:
  PageAllocator(std::uint64_t page_size) : page_size_(page_size) {
  }

  ~PageAllocator() {
    for (void *page : pages_)
      ::operator delete(page);
  }

  void *Allocate() {
    void *page = ::operator new(page_size_);
    pages_.push_back(page);
    return page;
  }

  std::uint64_t Allocated() const noexcept {
    return pages_.size();
  }
};

template<typename Tp>
class FixedAllocator {
  PageAllocator page_allocator_;
  std::vector<Tp *> free_mem;
  std::uint64_t size;

  void Get_mem() {
    Tp *i = static_cast<Tp *>(page_allocator_.Allocate());
    for (auto j = i; j < i + size; j++) {
      free_mem.push_back(j);
    }
  }

 public:
  explicit FixedAllocator(std::uint64_t page_size) :
      page_allocator_(page_size * sizeof(Tp)),
      size(page_size) {
    Get_mem();
  }

  Tp *Allocate() {
    if (free_mem.empty()) {
      Get_mem();
    }
    auto ref = free_mem[free_mem.size() - 1];
    free_mem.pop_back();
    return ref;
  }
  void Deallocate(Tp *p) {
    free_mem.push_back(p);
  }
  const PageAllocator &InnerAllocator() const noexcept {
    return page_allocator_;
  }
};

int main() {
  srand(666);

  const auto require_allocs = [](std::uint64_t expected, std::uint64_t actual) -> void {
    if (expected == actual)
      return;
    std::cout << "Invalid count of page allocations" << std::endl;
    std::cout << "Expected: " << expected << std::endl;
    std::cout << "You have: " << actual << std::endl;
    std::exit(0);
  };

  {
    FixedAllocator<int> a(1);
    auto p1 = a.Allocate();
    auto p2 = a.Allocate();
    a.Deallocate(p1);
    a.Deallocate(p2);
    p1 = a.Allocate();
    p2 = a.Allocate();
    require_allocs(2, a.InnerAllocator().Allocated());
  }

  {
    FixedAllocator<std::string> a(10);
    for (int i = 0; i < 10; ++i)
      a.Allocate();
    require_allocs(1, a.InnerAllocator().Allocated());
  }

  {
    FixedAllocator<std::string> a(100);
    for (int i = 0; i < 50; ++i)
      a.Deallocate(a.Allocate());
    require_allocs(1, a.InnerAllocator().Allocated());
  }

  {
    FixedAllocator<std::string> a(1);
    for (int i = 0; i < 5; ++i)
      a.Deallocate(a.Allocate());
    require_allocs(1, a.InnerAllocator().Allocated());
  }

  {
    FixedAllocator<std::string> a(1);
    for (int i = 0; i < 50; ++i) {
      a.Allocate();
      a.Deallocate(a.Allocate());
    }
    require_allocs(51, a.InnerAllocator().Allocated());
  }

  {
    FixedAllocator<std::string> a(100);
    for (int i = 0; i < 500; ++i) {
      a.Allocate();
      a.Deallocate(a.Allocate());
    }
    require_allocs(6, a.InnerAllocator().Allocated());
  }

  {
    FixedAllocator<std::string> a(100);
    for (int i = 0; i < 1000; ++i) {
      a.Allocate();
      a.Deallocate(a.Allocate());
    }
    require_allocs(11, a.InnerAllocator().Allocated());
  }

  {
    FixedAllocator<std::string> a(1000000);
    for (int i = 0; i < 1000000; ++i) {
      a.Allocate();
      a.Deallocate(a.Allocate());
    }
    require_allocs(2, a.InnerAllocator().Allocated());
  }

  {
    FixedAllocator<char> a(100);
    std::vector<char *> store;
    for (int i = 0; i < 100; ++i)
      store.push_back(a.Allocate());
    for (int i = 0; i < 10000; ++i) {
      const int rnd = rand() % 100;
      a.Deallocate(store[rnd]);
      if (a.Allocate() != store[rnd]) {
        std::cout << "Invalid allocation result" << std::endl;
        return 0;
      }
    }
  }

  std::cout << "GOOD" << std::endl;
  return 0;
}