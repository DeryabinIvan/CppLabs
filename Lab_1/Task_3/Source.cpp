#include <iostream>

using namespace std;

int main() {

	int n, k;
	cin >> n >> k;

	int m = 0;
	for (int i = k+1; i < n; i++) {
		if (n % i == 0 && i % 2 != 0) {
			m++;
		}
	}

	cout << "m: " << m << endl;
	system("pause");

	return 0;
}