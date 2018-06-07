#pragma once

#include <string>
#include <iostream>

class Flat {
	unsigned short floor, rooms;
	float area;
	char* street = nullptr;

	public:
		Flat(unsigned short rooms, float area, unsigned short floor, const char* street);
		Flat(const Flat& copy);
		Flat();
		~Flat();

		unsigned short getRooms() const { return rooms; }
		float getArea() const { return area; }
		unsigned short getFloor() const { return floor; }
		const char* getStreet() const { return street; }

		friend std::ostream& operator<<(std::ostream& os, const Flat& f);

		bool operator==(const Flat& f);
		bool operator!=(const Flat& f);
		Flat& operator=(const Flat& f);
};

