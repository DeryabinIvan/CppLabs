#include <iostream>
#include <limits>

using namespace std;

int main() {

	int n;
	cin >> n;

	int* mas = new int[n];
	int max = INT_MIN, ind;
	for (int i = 0; i < n; i++) {
		cin >> i[mas]; // mas[i] <=> *(mas + i) <=> *(i + mas) <=> i[mas]

		if (mas[i] > max) {
			max = mas[i];
			ind = i;
		}
	}

	for (int i = 0; i < ind; i+=2){
		mas[i] *= max;

		cout << mas[i] << ' ';
	}

	cout << endl;

	system("pause");
	delete[] mas;

	return 0;
}