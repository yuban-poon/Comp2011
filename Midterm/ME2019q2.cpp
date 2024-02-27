#include <iostream>
using namespace std;

int& fun(int x, int& y) {
	x = 2*x;
	y = y*x;
	return y;
}

int main() {
  int a = 1, b = 3, result = 0;
	cout << fun(a, b) << endl;
	result = fun(a+4 , b);
	cout << result << endl;
	fun(a, b) *= 10;
	cout << a << ", " << b << endl;
  return 0;
}