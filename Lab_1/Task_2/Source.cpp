#include <iostream>

using namespace std;

double f(double x) {
	if (x >= -2 && x <= 2)
		return x*x;

	return 4;
}

int main() {

	double a;
	cin >> a;

	cout << "f(a): " << f(a) << endl;

	system("pause");

	return 0;
}