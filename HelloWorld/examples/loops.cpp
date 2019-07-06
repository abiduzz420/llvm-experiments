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

int main() {
	cout << "Addition of 3 and 1 is " << addFunc(3,1) << endl;
	countDown();

	return 0;
}
