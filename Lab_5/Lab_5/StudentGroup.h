#pragma once

#include "List.h"
#include "Date.h"
#include "Student.h"

#include <iostream>

class StudentGroup{
	private:
		//Methods for list sorting

		List<Student*> sorted;
		bool findInList(Date s, List<Date>& list);
		void sortList();

	public:
		void addStudent(Student* student);
		void addStudent(char* _fio, Date bdate, char* _number);
		void readFromStream(std::istream& in);

		Student* findByBDate(Date date);
		Student* findByFIO(const char* name);
		Student* findByNumber(const char* number);

		bool remove(const char* name);

		void print();

		void sortByBDate();
};

