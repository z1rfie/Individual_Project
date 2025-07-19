#include <iostream>
#include <clocale>
#include "time.h"

Time::Time() : _hours(0), _minutes(0), _seconds(0) {}

Time::Time(int h, int m, int s) {
    if (h < 0 || h > 24) throw std::invalid_argument("„асы должны находитьс€ в диапазоне от 0 до 24!");

    if (m < 0 || m > 60) throw std::invalid_argument("ћинуты должны находитьс€ в диапазоне от 0 до 60!");

    if (s < 0 || s > 60) throw std::invalid_argument("—екунды должны находитьс€ в диапазоне от 0 до 60!");

    _hours = h;
    _minutes = m;
    _seconds = s;
}

Time::Time(const Time& other) {
    if (&other == nullptr) {
        throw std::invalid_argument("”казатель времени не может быть равен нулю");
    }
    _hours = other._hours;
    _minutes = other._minutes;
    _seconds = other._seconds;
}
