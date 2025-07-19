#pragma once

class Date {
	int _day;
	int _month;
	int _year;
public:
	Date();
	Date(int, int, int);
	Date(const Date&);
private:
	bool isDayValid(int day, int month, int year) const;
};