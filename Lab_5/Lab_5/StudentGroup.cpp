#include "StudentGroup.h"

List<Student*> students;

void StudentGroup::addStudent(Student* s) {
	students.addInEnd(s);
}
void StudentGroup::addStudent(char * _fio, Date bdate, char * _number){
	students.addInEnd(new Student(_fio, bdate, _number));
}

void StudentGroup::readFromStream(std::istream& in){
	in.ignore();
	while (!in.eof()) {
		char buf[255];
		in.getline(buf, 255);

		if (strlen(buf) == 0) return;

		Date d;

		char *fio, *phone, *date;
		fio = strtok(buf, ";");
		phone = strtok(NULL, ";");
		date = strtok(NULL, ";");

		char *day, *month, *year;
		day = strtok(date, ".");
		month = strtok(NULL, ".");
		year = strtok(NULL, ".");

		d.day = atoi(day);
		d.month = atoi(month);
		d.year = atoi(year);

		students.addInEnd(new Student(fio, d, phone));
	}
}

Student* StudentGroup::findByBDate(Date date) {
	if (students.getSize() < 1) return nullptr;

	students.begin();
	Student** st;
	for (st = students.getElement(); st; st = students.getElement())
		if ((*st)->getBDate() == date)
			return *st;
	return nullptr;
}
Student* StudentGroup::findByFIO(const char* name) {
	if (students.getSize() < 1) return nullptr;

	students.begin();
	Student** st;
	for (st = students.getElement(); st; st = students.getElement()) {
		if (!strcmp((*st)->getFIO(), name))
			return *st;
	}
	return nullptr;
}
Student* StudentGroup::findByNumber(const char* number) {
	if (students.getSize() < 1) return nullptr;

	students.begin();
	Student** st;
	for (st = students.getElement(); st; st = students.getElement())
		if (!strcmp((*st)->getNumber(), number))
			return *st;
	return nullptr;
}

bool StudentGroup::remove(const char* name){
	Student* find = findByFIO(name);

	if (!find) return false;

	List<Student*> tmp;

	students.begin();
	Student** st;
	for (st = students.getElement(); st; st = students.getElement())
		if ((*st) != find) tmp.addInEnd(*st);

	students.clear();
	tmp.begin();
	for (st = tmp.getElement(); st; st = tmp.getElement())
		students.addInEnd(*st);

	return true;
}

void StudentGroup::print() {
	std::cout << "Student group:\n";
	if (students.getSize() > 0) {
		students.begin();
		Student** s;
		for (s = students.getElement(); s; s = students.getElement()) {
			(*s)->print();
		}
	}
}

void StudentGroup::sortByBDate() {
	sortList();

	students.clear();

	sorted.begin();
	Student** st;
	for (st = sorted.getElement(); st; st = sorted.getElement())
		students.addInEnd(*st);

	sorted.clear();
}

bool StudentGroup::findInList(Date date, List<Date>& list) {
	if (list.getSize() < 1) return false;

	list.begin();
	Date* elem;

	while (elem = list.getElement()) {
		if (*elem == date)
			return true;
	}

	return false;
}
void StudentGroup::sortList() {
	static List<Date> elems;

	if (elems.getSize() == students.getSize()) {
		elems.clear();
		return;
	}

	students.begin();
	Student** elem;

	Date max;
	while (elem = students.getElement()) {
		if ((*elem)->getBDate() > max && !findInList((*elem)->getBDate(), elems))
			max = (*elem)->getBDate();
	}

	students.begin();
	while (elem = students.getElement()) {
		if ((*elem)->getBDate() == max && !findInList((*elem)->getBDate(), elems))
			sorted.addInEnd(*elem);
	}
	elems.addInEnd(max);
	sortList();
}