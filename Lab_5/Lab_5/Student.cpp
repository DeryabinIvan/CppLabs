#include "Student.h"

Date date;
char* fio, *number;

Student::Student(char* _fio, Date bdate, char* _number){
	fio = new char[strlen(_fio)];
	strcpy(fio, _fio);

	number = new char[strlen(_number)];
	strcpy(number, _number);

	date.day	= bdate.day;
	date.month	= bdate.month;
	date.year	= bdate.year;
}

void Student::setNumber(char* _number){
	if (number) delete[] number;

	number = new char[strlen(_number)];
	strcpy(number, _number);
}
void Student::setFIO(char* _fio){
	if (fio) delete[] fio;

	fio = new char[strlen(_fio)];
	strcpy(fio, _fio);
}

const char* Student::getFIO(){
	return fio;
}
Date Student::getBDate(){
	return date;
}
const char* Student::getNumber(){
	return number;
}

void Student::print(){
	std::cout << "Student: " << fio << ' ' << (int)date.day << '.' << (int)date.month << '.' << date.year << "\nPhone number: +" << number << std::endl;
}
