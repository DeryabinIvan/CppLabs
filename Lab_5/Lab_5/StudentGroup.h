#pragma once

#include "List.h"
#include "Date.h"
#include "Student.h"

class StudentGroup{
	public:
		void addStudent(Student& student);
		void addStudent(char* _fio, Date bdate, char* _number);

		Student* findByBDate(Date date);
		Student* findByFIO(char* name);
		Student* findByNumber(const char* number);

		void print();

		void sortByBDate();
};

