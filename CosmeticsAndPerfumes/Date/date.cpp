#include <iostream>
#include <clocale>
#include "date.h"

bool Date::isDayValid(int day, int month, int year) const {
    if (month == 2) {
        // проверка на високосный год для февраля
        bool isLeap = (year % 400 == 0) || (year % 100 != 0 && year % 4 == 0);
        return day <= (isLeap ? 29 : 28);
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11) {
        return day <= 30;
    }
    return day <= 31;
}

Date::Date() : _day(1), _month(1), _year(2020) {}

Date::Date(int d, int m, int y) {
    if (y < 2019 || y > 2026) {
        throw std::invalid_argument("Год должен быть в диапазоне от 2019 до 2026");
    }

    if (m < 1 || m > 12) {
        throw std::invalid_argument("Месяц должен быть в диапазоне от 1 до 12");
    }

    if (d < 1 || !isDayValid(d, m, y)) {
        throw std::invalid_argument("Некорректный день для указанного месяца и года");
    }

    _day = d;
    _month = m;
    _year = y;
}

Date::Date(const Date& other) {
    if (&other == nullptr) {
        throw std::invalid_argument("Указатель даты не может быть равен нулю");
    }
    _day = other._day;
    _month = other._month;
    _year = other._year;
}