#include "Set.h"
#include <memory>


Set::Set(){
	count = 0;
	set = new int[size = 10];
}
Set::Set(int _size) {
	count = 0;
	set = new int[size = _size];
}
Set::~Set(){
	count = 0;
	size = 0;

	delete[] set;
}

void Set::add(int a) {
	if (count+1 > size) {
		int* copy = new int[size];
		
		memcpy(copy, set, sizeof(int)*size);

		delete[] set;
		size += 5;
		set = new int[size];

		memcpy(set, copy, sizeof(int)*(size-5));
		delete[] copy;
	}

	set[count++] = a;
}
void Set::remove(int a) {
	if (count < 1) return;

	for (int i = 0; i < count; i++)
		if (set[i] == a) {
			set[i] = 0;
			count--;
		}
}
bool Set::contain(int a) {
	for (int i = 0; i < count; i++)
		if (set[i] == a)
			return true;
	return false;
}

Set& Set::operator<<(int a) {
	add(a);
	return *this;
}
Set& Set::operator>>(int a) {
	remove(a);
	return *this;
}

Set& Set::operator+(Set& a){
	Set *tmp = new Set();

	for (int i = 0; i < count; i++)
		*tmp << set[i];

	for (int i = 0; i < a.count; i++) {
		if (!(*tmp).contain(a.set[i]))
			*tmp << a.set[i];
	}
	return *tmp;
}
Set& Set::operator-(Set& b) {
	Set *tmp = new Set();

	for (int i = 0; i < count; i++) {
		if (!b.contain(set[i]))
			*tmp << set[i];
	}
	return *tmp;
}

bool Set::operator>(const Set& a) const {
	return count > a.count;
}
bool Set::operator<(const Set& a) const {
	return count < a.count;
}
bool Set::operator==(const Set& a)const {
	if (count != a.count) return false;

	for (int i = 0; i < count; i++)
		for (int j = 0; j < count; j++)
			if (set[i] != a.set[j])
				return false;

	return true;
}

std::ostream& operator<<(std::ostream& s, const Set& a){
	s << "Set: ";
	if(a.count > 0)
		for (int i = 0; i < a.count; i++) {
		s << a.set[i] << ' ';
	}
	else s << "EMPTY";

	return s;
}
