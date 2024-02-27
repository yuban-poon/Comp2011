#include <iostream>	
using namespace std;
int main(){
	float x = -2, y = 1;
	cout << [](float a, float b) {a=(a<0)?-a:a; return ((a+b)/2);}(x, y);
	cout << ", " << x << ", " << y << endl;

	float x = -2, y = 1;
	cout << [](float a, float b) -> int {a=(a<0)?-a:a; return ((a+b)/2);}(x, y);
	cout << ", " << x << ", " << y << endl;

	float x = -2, y = 1;
	cout << [=]() mutable { x=(x<0)?-x:x; return ((x+y)/2);}();
	cout << ", " << x << ", " << y << endl;

	float x = -2, y = 1;
	cout << [&]() { x=(x<0)?-x:x; return ((x+y)/2);}();
	cout << ", " << x << ", " << y << endl;

	float x = 1, y = 0;
	auto f = [&x, y]() { x=(x<0)?-x:x; return ((x+y)/2);};
	x = -2; y = 1;
	cout << f();
	cout << ", " << x << ", " << y << endl;
}