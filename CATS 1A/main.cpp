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
#include <map>
#include <iomanip>
#include <sstream>
#include <cassert>
#include "date.h"

class PrimeNumberGenerator {
  public:
    int start;
    int next_prime;
    explicit PrimeNumberGenerator(int start){
        this->start = start;
    }
    int GetNextPrime(){
        for(int i = start; i < 1000; i++){
            int a = 1;
            for(int j = 1; j < i; j++){
                if(i % j == 0){
                    a++;
                }
            }
            if(a == 2){
                next_prime = i;
                break;
            }
        }
        start = next_prime + 1;
        return  next_prime;
    }
};

int main() {
    int start, num;
    std::cin >> start >> num;
    PrimeNumberGenerator gen(start);
    for (int i = 0; i < num; ++i) {
        std::cout << gen.GetNextPrime() << " ";
    }
}