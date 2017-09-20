#include <iostream>
#include <cmath>

using namespace std;

int fact(int a) {
	return a < 2 ? 1 : a*fact(a - 1);
}

int main() {

	int n;
	double x;

	cin >> n >> x;

	double res = 1;

	for (int k = 1; k <= n; k++) {
		res *= (pow(1 - x, k + 1) + 1) / (pow(fact(k - 1) + 1, 2));
	}

	cout << "Result: " << res << endl;

	system("pause");

	return 0;
}