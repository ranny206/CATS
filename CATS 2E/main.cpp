#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <unordered_map>

using namespace std;

using ObjectId = unsigned long long int;

struct GameObject {
  ObjectId id;
  string name;
  size_t x;
  size_t y;
};

bool operator>(const GameObject &a, const GameObject &b) {
  return a.id > b.id;
}
bool operator<(const GameObject &a, const GameObject &b) {
  return a.id < b.id;
}

template<class Tp, template<class> class Compare>
class DereferenceCompare {
  Compare<Tp> comp;

 public:
  bool operator()(const Tp *const a, const Tp *const b) const {
    return comp(*a, *b);
  }
};

class GameDatabase {
 public:
  GameDatabase() = default;
  std::map<ObjectId, GameObject, std::greater<ObjectId>> data_base_id;
  std::map<std::pair<size_t, size_t>,
           std::set<GameObject *, DereferenceCompare<GameObject, std::greater>>> data_base_cord;
  std::unordered_map<string,
                     std::set<GameObject *, DereferenceCompare<GameObject, std::greater>>> data_base_name;
  std::set<GameObject> obj_set;

  void Remove(ObjectId id) {
    auto i = data_base_id.find(id);
    if (i != data_base_id.end()) {
      data_base_id.erase(i);
      auto obj = i->second;
      data_base_name[obj.name].erase(&obj);
      auto p = std::make_pair(obj.x, obj.y);
      data_base_cord[p].erase(&obj);
      //obj_set.erase(obj);
    }
  }

  void Insert(ObjectId id, string name, size_t x, size_t y) {
    GameObject tmp;
    tmp.id = id;
    tmp.name = name;
    tmp.x = x;
    tmp.y = y;
    Remove(id);
    auto k = obj_set.find(tmp);
    if (k != obj_set.end()) {
      obj_set.erase(k);
    }
    auto it = obj_set.insert(tmp);
    auto i = data_base_id.find(id);
    auto p = std::make_pair(tmp.id, *it.first);
    data_base_id.insert(p);
    data_base_name[name].insert(const_cast<GameObject *>(&(it.first.operator*())));
    auto c = std::make_pair(tmp.x, tmp.y);
    data_base_cord[c].insert(const_cast<GameObject *>(&(it.first.operator*())));
  }

  vector<GameObject> DataByName(string name) const {
    std::vector<GameObject> name_vec;
    auto it = data_base_name.find(name);
    if (it == data_base_name.end()) {
      return name_vec;
    }
    auto s = it->second;
    for (auto i : s) {
      name_vec.push_back(*i);
    }
    return name_vec;
  }

  vector<GameObject> DataByPosition(size_t x, size_t y) const {
    std::vector<GameObject> pos_vec;
    auto p = std::make_pair(x, y);
    auto it = data_base_cord.find(p);
    if (it == data_base_cord.end()) {
      return pos_vec;
    }
    auto &s = it->second;
    for (auto i : s) {
      pos_vec.push_back(*i);
    }
    return pos_vec;
  }

  vector<GameObject> Data() const {
    std::vector<GameObject> all_vec;
    for (auto i : data_base_id) {
      all_vec.push_back(i.second);
    }
    return all_vec;
  }
};

template<class Stream>
void operator<<(Stream &s, const GameObject &obj) {
  s << obj.id << ' ' << obj.name << ' ' << obj.x << ' ' << obj.y << '\n';
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  GameDatabase db;
  // *******************************
  size_t n;
  cin >> n;
  for (size_t i = 0; i < n; ++i) {
    size_t op_type, id, x, y;
    string name;
    cin >> op_type >> id;
    if (op_type) // remove operation
    {
      db.Remove(id);
      continue;
    }
    cin.ignore(1);
    cin >> name >> x >> y;
    db.Insert(id, std::move(name), x, y);
  }
  // *******************************
  for (size_t i = 0; i <= 49; ++i)
    for (size_t j = 0; j <= 49; ++j)
      for (const auto &e : db.DataByPosition(i, j))
        cout << e;
  for (char i = 'a'; i <= 'z'; ++i)
    for (char j = 'a'; j <= 'z'; ++j)
      for (const auto &e : db.DataByName(string() + i + j))
        cout << e;
  for (const auto &e : db.Data())
    cout << e;
  cout.flush();
  return 0;
}