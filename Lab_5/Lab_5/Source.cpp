#include <iostream>

#include "Date.h"
#include "Student.h"
#include "StudentGroup.h"

using namespace std;

int main() {
	enum MENU{ ADD=1, REMOVE, FIND, PRINT, SORT, HELP, EXIT };
	enum FIND_BY{ NAME=1, PHONE, DATE, RETURN };

	short menu_key;

	StudentGroup group;

	while (true) {
		printf("Menu:\n\t%d) Add student\n\t%d) Remove student by FIO\n\t%d) Find student\n\t%d) Print student group\n\t%d) Sort by birth date\n\t%d) Help\n\t%d) Exit\n", ADD, REMOVE, FIND, PRINT, SORT, HELP, EXIT);

		cin >> menu_key;
		system("cls");
		switch (menu_key) {
			case ADD:
				cout << "Press enter to stop\n";
				group.readFromStream(cin);
				break;

			case REMOVE:
				system("cls");
				cout << "Enter student FIO: ";

				char buf[255];
				cin.ignore();
				cin.getline(buf, 255);

				if (group.remove(buf)) cout << "Student deleted!\n";
				else cout << "Nothing deleted\n";

				break;

			case FIND:
				system("cls");
				printf("Find student by..\n\t%d) Name\n\t%d) Phone\n\t%d) Birth day\n\t%d) Exit\n", NAME, PHONE, DATE, RETURN);

				cin >> menu_key;

				Student* find;
				if (menu_key < RETURN) {
					char buf[255];
					cin.ignore();
					cin.getline(buf, 255);

					if (menu_key == NAME) find = group.findByFIO(buf);
					else if (menu_key == PHONE) find = group.findByNumber(buf);
					else {
						Date d;

						char *day, *month, *year;
						day = strtok(buf, ".");
						month = strtok(NULL, ".");
						year = strtok(NULL, ".");

						d.day = atoi(day);
						d.month = atoi(month);
						d.year = atoi(year);

						find = group.findByBDate(d);
					}

					if (find) {
						cout << "\nOK I find: ";
						find->print();
					}
					else cout << "Sorry, noboby macth\n";
				}
				break;

			case SORT:
				group.sortByBDate();
				break;

			case HELP:
				cout << "Student input format: FIO;PHONE;DATE (phone without '+')" << endl;
				cout << "Date format: DD.MM.YYYY" << endl;
				cout << endl;
				break;

			case PRINT:
				group.print();
				break;

			case EXIT:
				return 0;
		}
	}

	return 0;
}