#include <iostream>

using namespace std;

int main() {

	int n;
	cin >> n;

	int* mas = new int[n];
	int even_count = 0;
	for (int i = 0; i < n; i++) {
		cin >> mas[i];

		if (!i && !(mas[i] % 2)) {
			cout << "First element must be odd" << endl;
			system("pause");
			return 0;
		}

		if (!(mas[i] % 2)) even_count++;
	}

	int* mas_c = new int[n + even_count];
	for (int i = 0, j = 0; i < n; i++, j++) {
		mas_c[j] = mas[i];

		if (!(mas[i] % 2))
			mas_c[++j] = mas_c[j - 2];
	}

	for (int i = 0; i < n + even_count; i++) cout << mas_c[i] << ' ';

	cout << endl;
	system("pause");

	delete[] mas;
	delete[] mas_c;

	return 0;
}