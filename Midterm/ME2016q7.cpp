#include <iostream>
#include <cmath>
using namespace std;

int num_digits(int n){
	if(n>0){
		return num_digits(n/10) + 1;	
	}else {
		return 0;
	}
}

int reverse(int n, int d){
	if (d > 0)
	{
		return (n%10)*pow(10, d-1) + reverse(n/10, d-1);
	}else {
		return 0;
	}
	
}

int main(){
	int num1=980;
	cout << num_digits(num1) << endl;
	cout << reverse(num1, num_digits(num1)) << endl;

	int num2=900;
	cout << num_digits(num2) << endl;
	cout << reverse(num2, num_digits(num2)) << endl;

	int num3=1234;
	cout << num_digits(num3) << endl;
	cout << reverse(num3, num_digits(num3)) << endl;
}