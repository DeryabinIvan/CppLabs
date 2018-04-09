#pragma once

struct Date{
	char day, month;
	short year;

	bool operator>(const Date& d1) {
		if (year  > d1.year) return true;
		if (month > d1.month) return true;
		if (day   > d1.day) return true;

		return false;
	}
	bool operator==(const Date& d1) {
		return d1.day == day && d1.month == month && d1.year == year;
	}
};