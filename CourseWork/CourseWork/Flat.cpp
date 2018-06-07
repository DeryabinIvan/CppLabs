#include "Flat.h"

Flat::Flat(unsigned short rooms, float area, unsigned short floor, const char* street) {
	this->area = area;
	this->floor = floor;
	this->rooms = rooms;

	this->street = new char[strlen(street) + 1];
	strcpy(this->street, street);
}
Flat::Flat(const Flat& copy) {
	this->area = copy.area;
	this->floor = copy.floor;
	this->rooms = copy.rooms;

	this->street = new char[strlen(copy.street)];
	strcpy(this->street, copy.street);
}
Flat::Flat() {
	floor = rooms = 0;
	area = -1;
	street = nullptr;
}
Flat::~Flat() {
	rooms = floor = 0;
	area = 0;
	delete[] street;
}

bool Flat::operator==(const Flat& f) {
	if (this->rooms == f.rooms && this->floor == f.floor) {
		if (this->area == f.area || ((this->area / f.area) * 100 <= 110 && (this->area / f.area) * 100 >= 90)) return true;
	}

	return false;
}
bool Flat::operator!=(const Flat & f) {
	return !(*this == f);
}
Flat& Flat::operator=(const Flat& f) {
	if (this != &f) {
		this->area = f.area;
		this->floor = f.floor;
		this->rooms = f.rooms;

		this->street = new char[strlen(f.street) + 1];
		strcpy(this->street, f.street);
	}

	return *this;
}

std::ostream& operator<<(std::ostream& os, const Flat& f) {
	os << "Addres: " << f.street << ", floor: " << f.floor
		<< ", rooms: " << f.rooms << ", total area: " << f.area;
	return os;
}
