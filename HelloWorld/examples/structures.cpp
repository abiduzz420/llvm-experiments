#include <iostream>

using namespace std;

struct Number {
	int val;
	bool isPrime;
	double inverse;
};

int addThem(struct Number a, struct Number b) {
	return a.val + b.val;
}

int main() {
	Number two = {2,true, 0.50};
	Number three = {3,true, 0.33};
	Number one = {1, false, 1.00};


	// cout << addThem(two,three) << endl;

	cout << one.val << one.isPrime << one.inverse << endl;;
	cout << one.val << two.val << three.val << endl;
	return 0;
}
