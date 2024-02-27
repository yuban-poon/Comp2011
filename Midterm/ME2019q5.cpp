#include <iostream>
using namespace std;

int string2int(const char s[], int x[]){
	int i = 0;
	while (s[i] != '\0'){
		x[i] = s[i] - '0';
		i++;
	}
	return i;
}

int main(){
	const int x[5] = {1, 2, 3, 4, 5};
}