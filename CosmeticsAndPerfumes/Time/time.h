#pragma once

class Time {
	int _hours;
	int _minutes;
	int _seconds;
public:
	Time();
	Time(int, int, int);
	Time(const Time&);
};