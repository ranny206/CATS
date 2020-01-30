#include <iostream>
#include <vector>
#include <set>

class Set {
 public:
  std::vector<int64_t> set;

  explicit Set(const std::vector<int64_t> &vec = std::vector<int64_t>()) {
    for (size_t i : vec) {
      auto tmp = std::find(set.begin(), set.end(), i);
      if (tmp == set.end()) {
        set.push_back(i);
      }
    }
  }

  bool Contains(int64_t value) const {
    auto tmp = std::find(set.begin(), set.end(), value);
    return !(tmp == set.end());
  }

  void Add(int64_t value) {
    if (!Contains(value)) {
      set.push_back(value);
    }
  }

  void Remove(int64_t value) {
    size_t pos = 0;
    for (size_t i = 0; i < set.size(); i++) {
      if (set[i] == value) {
        pos = i;
        set.erase(set.begin() + pos);
      }
    }
  }

  Set Union(const Set &s) const {
    Set s_union;
    for (size_t i : set) {
      s_union.Add(i);
    }
    for (size_t i : s.set) {
      if (!s_union.Contains(i)) {
        s_union.Add(i);
      }
    }
    return s_union;
  }

  Set Intersection(const Set &s) const {
    Set s_int;
    for (size_t i : s.set) {
      if (Contains(i)) {
        s_int.set.push_back(i);
      }
    }
    return s_int;
  }

  Set Difference(const Set &s) const {
    Set set_dif;
    for (size_t i : set) {
      if (!s.Contains(i)) {
        set_dif.Add(i);
      }
    }
    return set_dif;
  }
  Set SymmetricDifference(const Set &s) const {
    Set set_sym_dif;
    for (size_t i : s.set) {
      if (!Contains(i)) {
        set_sym_dif.Add(i);
      }
    }
    for (size_t i : set) {
      if (!s.Contains(i)) {
        set_sym_dif.Add(i);
      }
    }
    return set_sym_dif;
  }

  std::vector<int64_t> Data() const{
    return set;
  }
};