#include <iostream>

#include "Set.h"

using namespace std;

int main() {
	Set a(1), b;

	a << 5 << 12 << 48 << 42;
	cout << a << endl;
	b << 12 << -13 << 5 << 16 << 32;
	cout << b;

	Set c = a + b, d = a - b;

	cout << "\n" << c << "\n" << d << "\n";

	return 0;
}