#include <cassert>
#include <algorithm>
#include <cstring>
#include <deque>
#include <iostream>
#include <iterator>
#include <map>
#include <memory>
#include <queue>
#include <sstream>
#include <string>
#include <vector>


template<typename type, typename tp>
auto initialize_vector(type value, tp dim) {
    return std::vector<typeof(value)>(dim, value);
}

template<typename type, typename tp, typename ...Args>
auto initialize_vector(type value, tp dim, Args... args) {
    return std::vector<typeof(initialize_vector(value, args...))>(dim, initialize_vector(value, args...));
}


struct Test {
    int a = 0;

    Test(int a) : a(a) {}  // it is not marked explicit intentionally
    bool operator==(const Test &rhs) const {
        return a == rhs.a;
    }
};

int main() {
    {
        auto a = initialize_vector<int>(17, 10);
        std::vector<int> b(10, 17);
        assert(a == b);
    }

    {
        auto a = initialize_vector<int>(-1, 2, 3);
        std::vector<std::vector<int>> b(2, std::vector<int>(3, -1));
        assert(a == b);
    }

    {
        auto a = initialize_vector<std::string>("aba", 3, 4, 2);
        std::vector<std::vector<std::vector<std::string>>> b(3,
                                                             std::vector<std::vector<std::string>>(4,
                                                                                                   std::vector<std::string>(
                                                                                                           2, "aba")));
        assert(a == b);
    }

    {
        auto a = initialize_vector<Test>(4, 10);
        std::vector<Test> b(10, 4);
        assert(a == b);
    }

    {
        int v = 13;
        auto a = initialize_vector<int>(v, 2, 1);
        std::vector<std::vector<int>> b(2, std::vector<int>(1, v));
        assert(a == b);
    }

    {
        const int64_t w = 1;
        auto a = initialize_vector<int64_t>(w, 1);
        std::vector<int64_t> b(1, w);
        assert(a == b);
    }

    std::cout << 1;
}