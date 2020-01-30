#include <cassert>
#include <iostream>
#include <vector>
#include <functional>

using namespace std;

class Num {
public:
    Num(int value = 0, int modulo = 0){
        if(modulo != 0){
            this->value = value % modulo;
        }
        else{
            this->value = value;
        }
        this->modulo = modulo;
    }
    Num(const Num& other){
        value = other.value;
        modulo = 0;
    }

    int value;
    int modulo;
};

int main() {
    {
        Num a(1, 10);
        assert(a.value == 1);
        assert(a.modulo == 10);

        Num b(2001, 10);
        assert(b.value == 1);
        assert(b.modulo == 10);
    }

    {
        Num a(20000, 100);
        assert(a.value == 0);
        assert(a.modulo == 100);

        Num b = a;
        assert(b.value == 0);
        assert(b.modulo == 0);
    }

    {
        Num a(99, 100);
        assert(a.value == 99);
        assert(a.modulo == 100);

        Num b = a;
        assert(b.value == 99);
        assert(b.modulo == 0);
    }
    cout << 1 << endl;
}