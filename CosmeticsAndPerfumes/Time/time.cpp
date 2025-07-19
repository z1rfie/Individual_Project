#include <iostream>
#include <clocale>
#include "time.h"

Time::Time() : _hours(0), _minutes(0), _seconds(0) {}

Time::Time(int h, int m, int s) {
    if (h < 0 || h > 24) throw std::invalid_argument("���� ������ ���������� � ��������� �� 0 �� 24!");

    if (m < 0 || m > 60) throw std::invalid_argument("������ ������ ���������� � ��������� �� 0 �� 60!");

    if (s < 0 || s > 60) throw std::invalid_argument("������� ������ ���������� � ��������� �� 0 �� 60!");

    _hours = h;
    _minutes = m;
    _seconds = s;
}

Time::Time(const Time& other) {
    if (&other == nullptr) {
        throw std::invalid_argument("��������� ������� �� ����� ���� ����� ����");
    }
    _hours = other._hours;
    _minutes = other._minutes;
    _seconds = other._seconds;
}
