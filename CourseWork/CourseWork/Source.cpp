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
	Map<char, Flat> cardFile;
	Flat* request = nullptr;

	enum MENU { ADD = 1, PRINT, FIND, SAVE, LOAD, HELP, EXIT };

	short menu_key;

	bool run = true;

	while (run) {
		cout << "Card-file-based room finding program.\nMenu:\n";
		cout << '\t' << ADD << ")Enter request\n"
			<< '\t' << PRINT << ")Print card-file\n"
			<< '\t' << FIND << ")Find request in card-file\n"
			<< '\t' << SAVE << ")Save card-file\n"
			<< '\t' << LOAD << ")Load card-file\n"
			<< '\t' << HELP << ")Help\n"
			<< '\t' << EXIT << ")Exit\n";

		cin >> menu_key;
		system("cls");
		switch (menu_key) {
			case ADD:
			{
				cout << "Enter flat request: ";

				char buf[255];
				cin.ignore();
				cin.getline(buf, 255);
				
				if (buf[0] == '\0') continue;

				//Adress
				char* addr = strtok(buf, ",");

				//Floor
				char* sfloor = strtok(nullptr, ",");
				int floor = atoi(sfloor);

				//Rooms
				char* srooms = strtok(nullptr, ",");
				int rooms = atoi(srooms);

				//Area
				char* sarea = strtok(nullptr, ",");
				float area = atof(sarea);

				if (request) delete request;

				request = new Flat(rooms, area, floor, addr);
			}
			break;

			case PRINT:
			if (request) cout << "Request: " << *request << endl;
			if(cardFile.getKeysCount() > 0) cout << cardFile << endl;
			else cout << "Card-file is empty\n";
			break;

			case FIND:
			{
				if (!request) {
					cout << "You don`t enter request!\n";
					continue;
				}
				char alpha = request->getStreet()[0];
				alpha = tolower(alpha);

				bool find = false;

				if (cardFile.exist(alpha)) {
					cardFile.begin();
					for (const Flat* tmp = cardFile[alpha]; tmp; tmp = cardFile[alpha]) {
						if (*request == *tmp) {
							cout << *tmp << endl;
							find = true;
						}
					}
				} else find = false;

				if (find) {
					if (cardFile.getValCount(alpha) > 1) {
						cardFile.findBy(*request).remove(alpha);
					} else if (cardFile.getValCount(alpha) == 1) {
						cardFile.findBy(*request).remove(alpha);
					}
				} else {
					cout << "Sorry, but we nothing found.\n";
					cardFile.add(alpha, *request);

				}
			}
			break;

			case SAVE:
			save(cardFile);
			break;

			case LOAD:
			cardFile.clear();
			load(cardFile);
			break;

			case HELP:
			cout << "Request systacsis: ADRESS, FLAT, ROOMS, AREA\n";
			break;

			case EXIT:
			run = false;
			continue;
			break;
		}
	}

	if(request) delete request;

	system("pause");
	return 0;
}

void save(Map<char, Flat>& save) {
	ofstream file("card.file");
	file << save;
	file.close();

	cout << "OK\n";
}

void load(Map<char, Flat>& load) {
	ifstream file("card.file");
	if (!file.is_open()) {
		cout << "File not found! Check your save file in directory.\n";
		return;
	}
	
	file >> load;

	cout << "OK\n";
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