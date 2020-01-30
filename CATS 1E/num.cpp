#include "num.h"
#include <iostream>

Num::Num(int value, int modulo) : value(value), modulo(modulo) {}

Num &Num::operator=(const Num &other) {
  value = other.value;
  modulo = other.modulo;
  return *this;
}
Num Num::operator+(const Num &other) {
  int tmp = static_cast<int>((static_cast<int64_t>(this->value) + other.value) % this->modulo);
  Num result(tmp, this->modulo);
  return result;
}
Num Num::operator-(const Num &other) {
  int tmp = static_cast<int>((static_cast<int64_t>(this->value) - other.value) % this->modulo);
  Num result(tmp, this->modulo);
  return result;
}
Num Num::operator*(const Num &other) {
  int tmp = static_cast<int>((static_cast<int64_t>(this->value) * other.value) % this->modulo);
  Num result(tmp, this->modulo);
  return result;
}
Num Num::operator+(int num) {
  int tmp = static_cast<int>((static_cast<int64_t>(this->value) + num) % this->modulo);
  Num result(tmp, this->modulo);
  return result;
}

Num Num::operator-(int num) {
  int tmp = static_cast<int>((static_cast<int64_t>(this->value) - num) % this->modulo);
  Num result(tmp, this->modulo);
  return result;
}

Num Num::operator*(int num) {
  int tmp = static_cast<int>((static_cast<int64_t>(this->value) * num) % this->modulo);
  Num result(tmp, this->modulo);
  return result;
}
Num &Num::operator+=(const Num &other) {
  int tmp = static_cast<int>((static_cast<int64_t>(this->value) + other.value) % this->modulo);
  Num result(tmp, this->modulo);
  *this = result;
  return *this;
}

Num &Num::operator-=(const Num &other) {
  int tmp = static_cast<int>((static_cast<int64_t>(this->value) - other.value) % this->modulo);
  if (tmp < 0) {
    tmp += this->modulo;
  }
  Num result(tmp, this->modulo);
  *this = result;
  return *this;
}

Num &Num::operator*=(const Num &other) {
  int tmp = static_cast<int>((static_cast<int64_t>(this->value) * other.value) % this->modulo);
  Num result(tmp, this->modulo);
  *this = result;
  return *this;
}

Num &Num::operator+=(int num) {
  int tmp = static_cast<int>((static_cast<int64_t>(this->value) + num) % this->modulo);
  Num result(tmp, this->modulo);
  *this = result;
  return *this;
}

Num &Num::operator-=(int num) {
  int tmp = static_cast<int>((static_cast<int64_t>(this->value) - num) % this->modulo);
  if (tmp < 0) {
    tmp += this->modulo;
  }
  Num result(tmp, this->modulo);
  *this = result;
  return *this;
}

Num &Num::operator*=(int num) {
  int tmp = static_cast<int>((static_cast<int64_t>(this->value) * num) % this->modulo);
  Num result(tmp, this->modulo);
  *this = result;
  return *this;
}