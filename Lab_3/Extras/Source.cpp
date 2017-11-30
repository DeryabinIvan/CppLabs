#include <fstream>
#include <cstring>
#include <iostream>
using namespace std;

int main() {

	ifstream fin("INPUT.txt");
	ofstream fout("OUTPUT.txt");

	char buf[999];
	char *f_name, *s_name, *t_name;

	char* people[3];
	people[0] = new char[30];
	people[1] = new char[30];
	people[2] = new char[30];

	float mid = 0, mid_t = 0;
	int num1 = -1, num2, k = 0;

	setlocale(LC_ALL, "RUSSIAN");

	while (!fin.eof()) {
		fin.getline(buf, 999);
		
		f_name = strtok(buf, ";");
		s_name = strtok(NULL, ";");
		t_name = strtok(NULL, ";");

		char* tmp;
		while (tmp = strtok(NULL, ";")) {
			if (num1 == -1) {
				num1 = atoi(tmp);
				tmp = strtok(NULL, ";");
			}
			num2 = atoi(tmp);

			//cout << num1 << " " << num2 << endl;

			mid_t += (num2 - num1);
			k++;
			num1 = num2;
		}
		num1 = -1;
		mid_t /= k;

		//cout << f_name << " " << s_name << " " << t_name << ": " << mid_t << endl;

		if (mid_t > mid) {
			mid = mid_t;

			strcpy(people[0], f_name);
			strcpy(people[1], s_name);
			strcpy(people[2], t_name);
		}

	}

	fout << people[0] << " " << people[1] << " " << people[2] << ": " << mid;

	fin.close();
	fout.close();

	return 0;
}