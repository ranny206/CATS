#include <iostream>
#include <string>

//using namespace std;

class Date {
 public:
  int year;
  int month;
  int day;

  Date(int year, int month, int day) : year(year), month(month), day(day) {}
  bool IsLeap() const {
    if (this->year % 4 != 0) {
      return false;
    } else if (this->year % 100 != 0) {
      return true;
    } else {
      return this->year % 400 == 0;
    }
  }
  std::string ToString() const {
    std::string str_day = std::to_string(this->day);
    if (str_day.length() == 1) {
      str_day = '0' + str_day;
    }
    std::string str_month = std::to_string(this->month);
    if (str_month.length() == 1) {
      str_month = '0' + str_month;
    }
    std::string str_year = std::to_string(this->year);
    while (str_year.length() != 4) {
      str_year = '0' + str_year;
    }
    std::string date = str_day + '.' + str_month + '.' + str_year;
    return date;
  }

  int months[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  int leap_months[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  Date DaysLater(int days) const {
    int d = day;
    int m = month;
    int y = year;
    Date date(y, m, d);
    bool is_leap = false;
    while (days != 0) {
      date.day++;
      if (date.IsLeap()) {
        is_leap = true;
      }
      if (is_leap) {
        if (date.day > leap_months[date.month - 1]) {
          date.month++;
          date.day = 1;
        }
      } else {
        if (date.day > months[date.month - 1]) {
          date.month++;
          date.day = 1;
        }
      }
      if (date.month > 12) {
        date.year++;
        date.day = 1;
        date.month = 1;
      }
      days--;
    }
    return date;
  }

  int DaysLeft(const Date &date) const {
    int d = day;
    int m = month;
    int y = year;
    Date t_date(y, m, d);
    int day_counter = 0;
    bool is_leap = false;
    while (t_date.ToString() != date.ToString()) {
      day_counter++;
      t_date.day++;
      if (t_date.IsLeap()) {
        is_leap = true;
      }
      if (is_leap) {
        if (t_date.day > leap_months[t_date.month - 1]) {
          t_date.month++;
          t_date.day = 1;
        }
      } else {
        if (t_date.day > months[t_date.month - 1]) {
          t_date.month++;
          t_date.day = 1;
        }
      }
      if (t_date.month > 12) {
        t_date.year++;
        t_date.day = 1;
        t_date.month = 1;
      }
    }
    return day_counter;
  }
};