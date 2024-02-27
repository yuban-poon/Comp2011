#include <iostream>
using namespace std;

bool arrayAdd(const int a1[], const int a2[], int arrSum[], int size){
	int a=0, b=0, c = 0;
	for(int i=0;i<size;i++){
		int power = 1;
		for(int j=size-i-1;j>0;j--){
			power *= 10;
		}
		a += a1[i]*power;
		b += a2[i]*power;
	}
	c = a + b;
	int length = 0;
	int temp = c;
	while (temp/10 != 0)
	{
		length++;
		temp /= 10;
	}
	if (length > size)
	{
		return true;
	}
	
	for(int i=0;i<size;i++){
		int power = 1;
		for(int j=size-i-1;j>0;j--){
			power *= 10;
		}
		arrSum[i] = c/power;
	}
	return false;
}

int f1(int &p, int &q){
	int temp = p;
	q = p;
	p += q;
	return p;
}

int &f2(int &a, int b){
	a = a + b;
	return a;
}

int main(){
	int a = 1, b=3;

	if((a--) == 0)
		cout << "a-- == 0" << endl;
	else
		cout << "a-- != 0" << endl;

	cout << "a = " << a << endl;

	a = 1;
	if(a-- == 0)
		cout << "a-- == 0" << endl;
	else
		cout << "a-- != 0" << endl;

	cout << "a = " << a << endl;
	return 0;
}