#pragma once

struct Date{
	char day=-1, month=-1;
	short year=-1;

	bool operator>(const Date& d1) {
		if (year > d1.year) return true;
		else if (year == d1.year) {
			if (month > d1.month) return true;
			else if (month == d1.month && day > d1.day) return true;
		}

		return false;
	}
	bool operator==(const Date& d1) {
		return d1.day == day && d1.month == month && d1.year == year;
	}
};