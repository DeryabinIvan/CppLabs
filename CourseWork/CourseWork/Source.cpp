#include <iostream>

#include "Map.h"

using namespace std;

void printError(ERROR_CODE code) {
	switch (code) {
		case OK:
			cout << "OK\n";
			break;
		case NOT_FIND:
			cout << "NOT_FIND\n";
			break;
		case MULTIPLIE_ELEMNTS:
			cout << "MULTIPLIE_ELEMNTS\n";
			break;
	}
}

int main() {
	Map<int, const char*> test;

	int k1 = 1, k2 = 2, k3 = 3;

	test.add(k1, "a");
	test.add(k1, "b");
	test.add(k2, "string");
	test.add(k3, "Microsoft");

	const char *a, *b, *c, *m;
	//test.begin();
	a = *test[k1];
	b = *test[k1];

	c = *test[k2];
	m = *test[k3];

	cout << a << ' ' << b << ' ' << c << ' ' << ' ' << m << endl;

	ERROR_CODE code = test.remove(k2);
	printError(code);
	
	code = test.remove(k1);
	printError(code);

	code = test.findBy(a).remove(k1);
	printError(code);

	system("pause");
	return 0;
}