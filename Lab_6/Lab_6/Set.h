#pragma once

#include <iostream>

class Set{
	int* set;
	size_t size=0, count=0;

	public:
		Set();
		Set(int basic_size);
		~Set();

		void add(int a);
		void remove(int a);
		bool contain(int a);

		Set& operator<<(int);
		Set& operator>>(int);

		Set& operator+(Set&);
		Set& operator-(Set&);

		bool operator>(const Set&) const;
		bool operator<(const Set&) const;
		bool operator==(const Set&) const;

		friend std::ostream& operator<<(std::ostream&, const Set&);
};

