#include <fstream>
#include <iostream>

using namespace std;

//� ������� ������� ������������ ����
//���������� ������������ ������ (� ��� ����� � ���), ������� ������� ����
typedef struct stack {
	stack(int size) {
		s = new char[size];
		length = size;
		positon = 0;
	}

	bool isEmpty() { return positon ? false : true; }

	void push(char c){
		if (positon == length || positon + 1 == length) {
			s = new char[length+5];
			length += 5;
		}


		s[positon++] = c;
	}

	char pop() {
		if (isEmpty()) return -1;
		return s[positon--];
	}

	/*void print() {
		cout << "---------------" << endl;
		for (int i = 0; i < positon; i++)
			cout << s[i] << endl;
		cout << "---------------" << endl;
	}*/

	private:
		int length, positon;
		char* s;
};

int main() {

	ifstream fin("INPUT.txt");
	ofstream fout("OUTPUT.txt");

	stack r_bkt(10), l_bkt(10);
	char line[999];
	
	while (!fin.eof()) {
		fin.getline(line, 999);
		//��� ��� ����� �������� ������� ���������� � ����������� ������
		//� ����� �������� �� ����������
		for (int i = 0; line[i] != '\n' && i < 999; i++){
			switch (line[i]) {
				case '{':
				case '[':
				case '(':
					l_bkt.push(line[i]);
				break;

				case '}':
				case ']':
				case ')':
					r_bkt.push(line[i]);
					break;
			}
		}
	}

	for (int i = 0; !r_bkt.isEmpty() && !l_bkt.isEmpty(); i++){
		r_bkt.pop();
		l_bkt.pop();
	}

	//r_bkt.print();
	//l_bkt.print();

	if (r_bkt.isEmpty() && l_bkt.isEmpty()) fout << "���������";
	else fout << "�����������";

	fin.close();
	fout.close();

	return 0;
}