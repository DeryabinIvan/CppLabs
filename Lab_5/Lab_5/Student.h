#pragma once

#include "Date.h"
#include <cstring>
#include <iostream>

class Student{
	public:
		Student()=default;
		Student(char* fio, Date bdate, char* number);

		void setNumber(char* number);
		void setFIO(char* fio);

		const char* getFIO();
		Date getBDate();
		const char* getNumber();

		void print();
};

