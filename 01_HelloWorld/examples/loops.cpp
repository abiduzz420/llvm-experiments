#include <iostream>

using namespace std;

void countDown() {
	int x = 0;
	while(x < 10) {
		++x;
	}
}

int addFunc(int a, int b) {
	return a + b;
}

int factorial(int n) {
	int res = 1, x = 1;
	while(x != n) {
		res = res * x;
		x++;
	}
	return res;
}

int doubleIt(int n) {
	return n * 2;
}

int main() {
	cout << "Addition of 3 and 1 is " << addFunc(3,1) << endl;
	countDown();
	int x = 3;
	while(x < 10) {
		int y;
		if(x % 2 == 0) {
			y = doubleIt(x);
		} else {
			y = factorial(x);
		}
		if (y % 2 == 0) {
			cout << "y is even" << endl;
		} else {
			cout << "y is odd" << endl;
		}
		++x;
	}	
	return 0;
}
