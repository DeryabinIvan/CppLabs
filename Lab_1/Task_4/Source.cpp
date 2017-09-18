#include <iostream>

using namespace std;

int main() {

	int n;
	cin >> n;

	int a, k = 0;

	for (int i = 0; i < n; i++){
		cin >> a;

		if (a % 2 != 0) k++;
	}

	cout << "k: " << k << endl;
	system("pause");

	return 0;
}