#include <iostream>

using namespace std;

struct Number {
	int val;
	bool isPrime;
	double inverse;
};

int main() {
	Number one = {1, false, 1.00};
	cout << one.val << one.val << one.isPrime << one.inverse << endl;
	return 0;
}
