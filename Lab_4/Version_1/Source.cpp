#include <iostream>
#include <cstring>

using namespace std;

void addNote();
void findNote();
void sort();

struct Note {
	char* FI;
	unsigned int phone;
	unsigned short date[3];

	void print() {
		cout << "Name: " << FI << "\nPhone: " << phone << "\nDate: " << date[0] << "." << date[1] << "." << date[2] << endl;
	}
};

Note notes[8];

enum MENU{ENTER=1, FIND, PRINT, HELP, EXIT};

int main() {
	short menu_key;

	while (true) {
		
		printf("Menu:\n\t%d) Enter note\n\t%d) Find by month\n\t%d) Print note list\n\t%d) Help\n\t%d) Exit\n", ENTER, FIND, PRINT, HELP, EXIT);

		cin >> menu_key;
		system("cls");
		switch (menu_key) {
		case ENTER:
			addNote();
			sort();
			break;

		case FIND:
			findNote();
			break;

		case HELP:
			cout << "Note input format: FI;PHONE;DATE" << endl;
			cout << "Date format: DD.MM.YYYY" << endl;
			cout << endl;
			break;

		case PRINT:
			for (char i = 0; notes[i].FI && i < 8; i++)
				cout << notes[i].FI << endl;
			cout << endl;
			break;

		case EXIT:
			return 0;
		}
	}
}

int compare(const void* v1, const void* v2) {
	char *n1 = ((Note*)v1)->FI, *n2 = ((Note*)v2)->FI;

	for (unsigned short i = 0; n1[i] != ' ' && n2[i] != ' '; i++) {
		if ((n1[i] - n2[i]) != 0) return int(n1[i] - n2[i]);
	}

	return 0;
}

void sort() {
	char count = 0;

	while (notes[count].FI) count++;

	if (count < 2) {
		cout << "Nothing to sort" << endl << endl;
		return;
	}

	qsort(notes, count, sizeof(notes[0]), compare);

	cout << endl << "Sorted: " << endl;
	for (short i = 0; i < count; i++)
		cout << notes[i].FI << endl;
	cout << endl;
}

void addNote() {
	cout << "Enter - to exit or...\n";
	cin.ignore();
	for (short i = 0; i < 8; i++) {
		char line[255];

		cout << "Enter " << i + 1 << "-note: ";
		cin.getline(line, 255);

		if (!isalpha(line[0])) return;

		char* fi = strtok(line, ";");
		char* phone = strtok(nullptr, ";");
		char* date = strtok(nullptr, ";");

		notes[i].FI = new char[strlen(fi)];
		strcpy(notes[i].FI, fi);

		notes[i].phone = atoi(phone);
		
		notes[i].date[0] = atoi(strtok(date, "."));
		notes[i].date[1] = atoi(strtok(nullptr, "."));
		notes[i].date[2] = atoi(strtok(nullptr, "."));

		notes[i].print();
	}
}

void findNote() {
	short m;

	cin >> m;

	for (char i = 0; notes[i].FI && i < 8; i++)
		if (notes[i].date[1] == m)
			cout << "Find: " << notes[i].FI;
	cout << endl;
}