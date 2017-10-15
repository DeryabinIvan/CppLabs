#include <iostream>
#include <limits>

using namespace std;

/* Тестовые данные:
4
0 -1  5 20
-4 11 15 -5
76 23 -10 10
55 42 1 100

Что должно вывести: MAX: 76 MIN: -4
*/

int main() {

	int n;
	cin >> n;

	if (n % 2) {
		cout << "n must be even!" << endl;
		return 0;
	}

	int** m = new int*[n];

	for (int i = 0; i < n; i++)
		m[i] = new int[n];

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> m[i][j];

	int max = INT_MIN, min = INT_MAX, l_size = n / 2, last_l = l_size;
	int* line;

	for (int i = 0; i < n; i++){
		line = m[i];

		for (int j = 0; j < n; j++){
			if (l_size <= n - 2)
				if (j < n-l_size) {
					if (line[j] < min) min = line[j];
				} else {
					if (line[j] > max) max = line[j];
				}
				
			else //ошибка где-то здесь...
				if (j < l_size) {
					if (line[j] < min) min = line[j];
				} else {
					if (line[j] > max) max = line[j];
				}
		}

		if(last_l != l_size)
			if (l_size <= n - 2) l_size++;
			else l_size--;

		delete[] line;
	}

	cout << "MAX: " << max << " MIN: " << min << endl;
	system("pause");

	return 0;
}