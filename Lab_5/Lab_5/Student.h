#pragma once

#include "Date.h"
#include <cstring>
#include <iostream>

class Student{
	Date date;
	char* fio, *number;

	public:
		Student(char* fio, Date bdate, char* number);

		const char* getFIO();
		Date getBDate();
		const char* getNumber();

		void print();
};

