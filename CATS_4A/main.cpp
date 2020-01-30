#include <fstream>
#include <chrono>
#include <functional>
#include <vector>
#include <thread>
#include <iostream>

using namespace std;

template<typename TimePoint>
class basic_time_meter {
    function<TimePoint()> get_now_;
    function<double(TimePoint, TimePoint)> get_sec_;

    TimePoint begin_;
    TimePoint stop_;
    bool stopped_;

public:
    template<typename GetNow, typename GetSec>
    basic_time_meter(GetNow &&gn, GetSec &&gs) : get_now_(std::forward<GetNow>(gn)), get_sec_(std::forward<GetSec>(gs)),
                                                 begin_(get_now_()), stopped_(false) {}

    double seconds() const {
        if (stopped_)
            return get_sec_(begin_, stop_);
        return get_sec_(begin_, get_now_());
    }

    double restart() {
        const TimePoint now = get_now_();
        double result = seconds(now);
        stopped_ = false;
        begin_ = now;
        return result;
    }

    double stop() {
        if (stopped_)
            return seconds();
        stop_ = get_now_();
        stopped_ = true;
        return seconds(stop_);
    }

    void start() {
        if (!stopped_)
            return;
        stopped_ = false;
        begin_ += get_now_() - stop_;
    }

    bool stopped() const {
        return stopped_;
    }

private:
    double seconds(TimePoint now) const {
        if (stopped_)
            return get_sec_(begin_, stop_);
        return get_sec_(begin_, now);
    }
};

class time_meter : public basic_time_meter<chrono::high_resolution_clock::time_point> {
    using time_point = chrono::high_resolution_clock::time_point;

    static double get_seconds(time_point p1, time_point p2) {
        return static_cast<double>((p2 - p1).count()) / chrono::high_resolution_clock::period::den;
    }

public:
    time_meter() : basic_time_meter<time_point>(chrono::high_resolution_clock::now, get_seconds) {}
};

// **********************

void ___CaesarEncryptOneThread___(std::string *s) {
    for (char &c : *s)
        c = 'a' + (c + 3 - 'a') % 26;
}

//#include "caesar_encrypt.h"


void str_encrypt(int first, int last, std::string *s) {
    //std::string str = *s;
    for (int i = first; i < last; ++i) {
        s->operator[](i) = 'a' + (s->operator[](i) + 3 - 'a') % 26;
    }
    //*s = str;
}


void CaesarEncrypt(std::string *s) {
    std::vector<std::thread> vec;
    int first = 0;
    auto count = std::thread::hardware_concurrency();
    int l = s->length() / count;
    //int l = 13 / count;
    auto tmp = l;
    int a = count;
    for (int i = 0; i < count; i++) {
        vec.push_back(std::thread(str_encrypt, first, tmp, s));
        //str_encrypt(first, tmp, *s);
        first = tmp;
        if (i == count - 2) {
            tmp = s->length();
        } else {
            tmp += l;
        }
    }

    std::string s1 = *s;

    for (int j = 0; j < count; ++j) {
        vec[j].join();
    }
}


int main() {
//    ifstream input_file("input.txt");
//    ofstream output_file("output.txt");
    string s;
//    input_file >> s;
    cin >> s;
    string s2 = s;
    time_meter tm;
    ___CaesarEncryptOneThread___(&s2);
    const double one_thread_result = tm.seconds();

    tm.restart();
    CaesarEncrypt(&s);
    const double result = tm.seconds();

    const double x = result / one_thread_result;
    if (x > 0.75)
        cout << "So sloooooow\n\n" << "time / time_one_thread = " << x << endl;
    else
        cout << s << endl;

    return 0;
}