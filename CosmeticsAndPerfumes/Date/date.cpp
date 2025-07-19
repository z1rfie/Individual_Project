#include <iostream>
#include <clocale>
#include "date.h"

bool Date::isDayValid(int day, int month, int year) const {
    if (month == 2) {
        // �������� �� ���������� ��� ��� �������
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
        throw std::invalid_argument("��� ������ ���� � ��������� �� 2019 �� 2026");
    }

    if (m < 1 || m > 12) {
        throw std::invalid_argument("����� ������ ���� � ��������� �� 1 �� 12");
    }

    if (d < 1 || !isDayValid(d, m, y)) {
        throw std::invalid_argument("������������ ���� ��� ���������� ������ � ����");
    }

    _day = d;
    _month = m;
    _year = y;
}

Date::Date(const Date& other) {
    if (&other == nullptr) {
        throw std::invalid_argument("��������� ���� �� ����� ���� ����� ����");
    }
    _day = other._day;
    _month = other._month;
    _year = other._year;
}