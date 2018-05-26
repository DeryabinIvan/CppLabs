#include <iostream>

#include "Container.h"
#include "Queue.h"

using namespace std;

int main() {
	Queue test;
	Queue inseption;

	enum MENU { ADD_CONTAINER = 1, ADD_QUEUE, PRINT, EXIT };

	bool run = true;
	int key;

	while (run) {
		cout << ADD_CONTAINER << ")Add container in queue\n"
			<< ADD_QUEUE << ")Add queue\n"
			<< PRINT << ")Print queue\n"
			<< EXIT << ")Exit\n";
		cin >> key;
		switch (key) {
			case ADD_CONTAINER: {
				cout << "Enter empty string to stop\n";
				cin.ignore();

				bool read = true;
				while (read) {
					char buf[255];
					cin.getline(buf, 255);
					char* tmp;
					if (tmp = strtok(buf, " ")) {
						do {
							if (strchr(tmp, '.')) test << *(new Container((float)atof(tmp)));
							else if(!strcmp(tmp, "true")) test << *(new Container(true));
							else if(!strcmp(tmp, "false")) test << *(new Container(false));
							else if(isdigit(tmp[0])) test << *(new Container(atoi(tmp)));
							else {
								cout << "Incorrect input!\n";
								read = false;
								break;
							}

						} while (tmp = strtok(NULL, " "));
					}
					else {
						read = false;
						continue;
					}
				}
				break;
			}

			case ADD_QUEUE: {
				cout << "Enter empty string to stop\n";
				cin.ignore();

				bool read = true;
				while (read) {
					char buf[255];
					cin.getline(buf, 255);
					char* tmp;
					if (tmp = strtok(buf, " ")) {
						do {
							if (strchr(tmp, '.')) inseption << *(new Container((float)atof(tmp)));
							else if (!strcmp(tmp, "true")) inseption << *(new Container(true));
							else if (!strcmp(tmp, "false")) inseption << *(new Container(false));
							else if (isdigit(tmp[0])) inseption << *(new Container(atoi(tmp)));
							else {
								cout << "Incorrect input!\n";
								read = false;
								break;
							}
						} while (tmp = strtok(NULL, " "));
					}
					else {
						read = false;
						continue;
					}
				}
				test << inseption;
				break;
			}

			case PRINT: {
				char buf[1000];
				test.toString(buf);
				cout << buf << endl;

				inseption.toString(buf);
				cout << buf << endl;
				break;
			}
			case EXIT:
				run = false;
				break;
		}
	}

	system("pause");
	return 0;
}