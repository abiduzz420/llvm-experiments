#include <iostream>

using namespace std;

int max(int,int);

int main() {
	int maxval;
	maxval = max(22,23);
	return maxval;
}
	
int max(int i, int j) {
int k;
if(i>j) k=i;
else k=j;
return k;
}
