#ifndef CATS_1E_NUM_H
#define CATS_1E_NUM_H
#pragma once
#include <iostream>

class Num {
 public:
  Num(int value, int modulo);

  Num& operator=(const Num& other);

  Num operator+(const Num& other);
  Num operator-(const Num& other);
  Num operator*(const Num& other);
  Num operator+(int num);
  Num operator-(int num);
  Num operator*(int num);

  Num& operator+=(const Num& other);
  Num& operator-=(const Num& other);
  Num& operator*=(const Num& other);
  Num& operator+=(int num);
  Num& operator-=(int num);
  Num& operator*=(int num);

  int value;
  int modulo;
};

#endif //CATS_1E_NUM_H
