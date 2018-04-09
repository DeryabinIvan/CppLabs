#include <iostream>

#include "Date.h"
#include "Student.h"
#include "StudentGroup.h"

using namespace std;

int main() {
	Date date1, date2, date3;

	date1.day = 15;
	date1.month = 1;
	date1.year = 1999;

	date2.day = 1;
	date2.month = 10;
	date2.year = 1988;

	date3.day = 30;
	date3.month = 5;
	date3.year = 2005;

	Student din("X X X", date1, "79123168108");
	Student t1 ("T T T", date2, "1234567890");
	Student t2 ("Y Y Y", date3, "0987654321");

	din.print();
	t1.print();
	t2.print();

	system("pause");

	return 0;
}