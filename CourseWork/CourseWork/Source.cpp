#include <iostream>

#include "Map.h"

using namespace std;

int main() {
	Map<int, const char*> test;

	const char **h, **w;
	
	test.add(1, "Hello");
	test.add(1, "World");
	test.add(2, "String");
	test.add(3, "Another string: \"Visual Studio\"");

	test.begin();
	h = test.get(1);
	w = test.get(1);

	const char **a, **b;
	a = test.get(2);
	b = test.get(3);

	cout << *h << ' ' << *w << endl;
	cout << *a << ' ' << *b << endl;

	system("pause");
	return 0;
}