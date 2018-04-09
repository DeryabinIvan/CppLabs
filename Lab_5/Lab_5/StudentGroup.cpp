#include "StudentGroup.h"

List<Student> students;

void StudentGroup::addStudent(Student& s) {
	students.addInEnd(s);
}

void StudentGroup::addStudent(char * _fio, Date bdate, char * _number){
	students.addInEnd(Student(_fio, bdate, _number));
}

Student* StudentGroup::findByBDate(Date date) {
	students.begin();
	Student* st;
	for (st = students.getElement(); st; st = students.getElement())
		if (st->getBDate() == date)
			return st;
	return nullptr;
}
Student* StudentGroup::findByFIO(char* name) {
	students.begin();
	Student* st;
	for (st = students.getElement(); st; st = students.getElement()) {
		if (!strcmp(st->getFIO(), name) == 0)
			return st;
	}
	return nullptr;
}
Student* StudentGroup::findByNumber(const char* number) {
	students.begin();
	Student* st;
	for (st = students.getElement(); st; st = students.getElement())
		if (!strcmp(st->getNumber(), number))
			return st;
	return nullptr;
}

void StudentGroup::print() {
	if (students.getSize() > 0) {
		students.begin();
		Student* s;
		for (s = students.getElement(); s; s = students.getElement()) {
			s->print();
			std::cout << std::endl;
		}
	}
}

void StudentGroup::sortByBDate() {

}