#include <iostream>
#include <fstream>

#include "Map.h"
#include "Flat.h"

using namespace std;

void printError(ERROR_CODE code) {
	switch (code) {
		case OK:
			cout << "OK\n";
			break;
		case NOT_FIND:
			cout << "NOT_FIND\n";
			break;
		case MULTIPLIE_ELEMNTS:
			cout << "MULTIPLIE_ELEMNTS\n";
			break;
	}
}

void save(Map<char, Flat>& save);
void load(Map<char, Flat>& load);

int main() {
	Map<char, Flat> request;

	char k1 = 'a', k2 = 'b';
	request.add(k1, Flat(2, 20, 3, "sample"));
	request.add(k2, Flat(3, 30, 4, "wut"));

	cout << request << endl;

	save(request);

	request.clear();
	load(request);

	cout << request << endl;

	system("pause");
	return 0;
}

void save(Map<char, Flat>& save) {
	ofstream file("card.file");
	file << save;
	file.close();
}

void load(Map<char, Flat>& load) {
	ifstream file("card.file");
	if (!file.is_open()) {
		cout << "File not found! Check your save file in directory.";
	}
	
	file >> load;
}

std::istream& operator>>(std::istream& is, Map<char, Flat>& m) {
	while (!is.eof() && !is.fail()) {
		char buf[1024];
		is.getline(buf, 1024);

		char* pos = buf;
		//Key
		char key = buf[0];
		while (strchr(pos, 'A')) {
			//Adress
			pos = strchr(pos + 2, ':');
			ptrdiff_t comaPos = strchr(pos + 2, ',') - buf;

			size_t len = comaPos - (pos - buf + 2);
			char* addr = new char[len + 1];
			strncpy(addr, pos + 2, len);
			addr[len] = '\0';

			//Floor
			pos = strchr(pos + 2, ':');
			int floor = atoi(pos + 2);

			//Rooms
			pos = strchr(pos + 2, ':');
			int rooms = atoi(pos + 2);

			//Area
			pos = strchr(pos + 2, ':');
			float area = atof(pos + 2);

			Flat tmp(rooms, area, floor, addr);
			m.add(key, tmp);
			delete[] addr;
		}
	}

	return is;
}