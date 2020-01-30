#include <iostream>
#include <thread>
#include <functional>
#include <queue>
#include <mutex>

using namespace std;

class LotsOfData {
public:
    LotsOfData() {}
    explicit LotsOfData(int value) : value(value) {}
    LotsOfData(const LotsOfData&) = delete;
    LotsOfData(LotsOfData&& rhs) {
        this->value = rhs.value;
        rhs.value = -1;
    }
    LotsOfData& operator=(const LotsOfData&) = delete;
    LotsOfData& operator=(LotsOfData&& rhs) {
        this->value = rhs.value;
        rhs.value = -1;
        return *this;
    }
    ~LotsOfData() {}
    int value;
};

template <typename T>
class Queue {
public:

    T Pop() {
        T a;
        mut.lock();
        a = std::forward<T>(q.front());
        q.pop();
        mut.unlock();
        return a;
    }

    size_t Size() {
        return q.size();
    }

    template <typename U>
    void Push(U&& u) {
        mut.lock();
        q.push(std::forward<U>(u));
        mut.unlock();
    }

    template <typename ... U>
    void Emplace(U&& ...u) {
        q.emplace(std::forward<U>(u)...);
    }

private:
    std::queue<T> q;
    std::mutex mut;
};


Queue<LotsOfData> q;

void push(int n) {
    while (n > 0) {
        q.Push(LotsOfData(n));
        --n;
    }
}

void emplace(int n) {
    while (n > 0) {
        q.Emplace(n);
        --n;
    }
}

void pop(int n) {
    while (n > 0) {
        if (q.Size() > 0) {
            q.Pop();
            --n;
        }
    }
}

int main() {
    std::string query;
    std::cin >> query;
    if (query == "check") {
        while (std::cin >> query) {
            if (query == "push") {
                int value;
                std::cin >> value;
                q.Push(LotsOfData(value));
            }
            if (query == "emplace") {
                int value;
                std::cin >> value;
                q.Emplace(value);
            }
            if (query == "pop") {
                auto element = q.Pop();
                std::cout << element.value << " ";
            }
        }
    }
    else if (query == "thread_check") {
        int n;
        cin >> n;
        std::thread push_thread(std::bind(push, n/2));
        std::thread emplace_thread(std::bind(emplace, n - n/2));
        std::thread pop_thread(std::bind(pop, n));
        push_thread.detach();
        emplace_thread.detach();
        pop_thread.join();
        std::cout << 1 << std::endl;
    } else {
        std::cout << -1 << std::endl;
    }
}