#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

int main() {

	double x, y, z;
	double a, b;

	cin >> x >> y >> z;

	a = (sqrt(abs(x - 1)) - pow(abs(y), 1.0 / 3.0)) 
		/ (1.0 + pow(x, 2) / 2.0 + pow(y, 2) / 4.0);

	b = x*(asin(z) + pow(M_E, -(x + 3)));

	cout << "a: " << a << endl << "b: " << b;

	return 0;
}