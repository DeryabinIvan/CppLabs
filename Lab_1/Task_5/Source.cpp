#include <iostream>
#include <cmath>

using namespace std;

int main() {

	int n;
	double a;

	cin >> a >> n;

	double res=0;

	while (n > -1)
		res += 1.0 / (pow(a, pow(2, n--)));

	cout << "Result: " << res << endl;

	system("pause");

	return 0;
}