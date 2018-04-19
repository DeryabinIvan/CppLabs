#include "Student.h"

Student::Student(char* _fio, Date bdate, char* _number){
	fio = new char[strlen(_fio)];
	strcpy(fio, _fio);

	number = new char[strlen(_number)];
	strcpy(number, _number);

	date.day	= bdate.day;
	date.month	= bdate.month;
	date.year	= bdate.year;
}

const char* Student::getFIO(){
	return fio;
}
Date		Student::getBDate(){
	return date;
}
const char* Student::getNumber(){
	return number;
}

void Student::print(){
	std::cout << "Student: " << fio << ' ' << (int)date.day << '.' << (int)date.month << '.' << date.year << " +" << number << std::endl;
}
