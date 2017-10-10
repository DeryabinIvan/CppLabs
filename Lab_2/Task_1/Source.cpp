#include <iostream>

using namespace std;

int main() {

	int n;
	cin >> n;

	int* m = new int[n];

	int max=-999999999, ind=0;
	for (int i = 0; i < n; i++){
		cin >> m[i];

		if (m[i] > max) {
			max = m[i];
			ind = i;
		}
	}

	if (ind == n - 1) {
		cout << "Max value is last value in massive" << endl;
		return 0;
	}

	int sum = 0, mul = 1;
	for (int i = ind+1; i < n; i++){
		if (m[i]) 
			sum += m[i];
		else
			mul *= m[i];
	}

	sum *= 2; mul *= 2;

	cout << "Sum: " << sum << " Mul: " << mul << endl;
	system("pause");

	return 0;
}