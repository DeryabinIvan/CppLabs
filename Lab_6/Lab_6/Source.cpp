#include <iostream>
#include <time.h>

#include "Set.h"

using namespace std;

void printBool(bool t) {
	cout << (t ? "true" : "false");
}

int main() {
	enum MENU { ADD = 1, REMOVE, PRINT, COMPARE_TEST, HELP, EXIT };

	short menu_key;

	Set userSet, randomSet, sum, dif;

	while (true) {
		printf("Menu:\n\t%d) Add number\n\t%d) Remove number\n\t%d) Print set\n\t%d) Compare test\n\t%d) Help\n\t%d) Exit\n", ADD, REMOVE, PRINT, COMPARE_TEST, HELP, EXIT);

		cin >> menu_key;
		system("cls");
		switch (menu_key) {
			case ADD: {
				cout << "Enter empty string to stop\n";
				cin.ignore();

				bool read = true;

				int num;
				while (read) {
					char buf[255];
					cin.getline(buf, 255);
					char* tmp;
					if (tmp = strtok(buf, " ")) {
						do {
							if (!isdigit(tmp[0])) {
								cout << "Incorrect input! Please read help\n";
								read = false;
								break;
							}
							userSet << atoi(tmp);
						} while (tmp = strtok(NULL, " "));
					}
					else {
						read = false;
						continue;
					}
				}
			}
			break;

			case REMOVE:
				system("cls");
				cout << "Enter number to delete: ";
				
				int num;
				cin >> num;
				userSet >> num;

				break;
			case COMPARE_TEST:
				srand(time(0));

				for (int i = 0; i < 10; i++)
					randomSet << (-100 + rand() % 200);

				cout << "Random " << randomSet << endl;
				cout << "User " << userSet << endl;

				cout << "R_SET bigger U_SET "; printBool(randomSet > userSet); cout << endl;
				cout << "R_SET less U_SET "; printBool(randomSet < userSet); cout << endl;
				cout << "R_SET equal U_SET "; printBool(randomSet == userSet); cout << endl << endl;

				sum = randomSet + userSet, dif = randomSet - userSet;
				cout << "R_SET + U_SET " << sum << endl;
				cout << "R_SET - U_SET " << dif << endl << endl;

				break;

			case HELP:
				cout << "Number format: NUM NUM NUM..." << endl;
				cout << endl;
				break;

			case PRINT:
				cout << userSet << endl;
				break;

			case EXIT:
				return 0;
		}
	}

	return 0;
}