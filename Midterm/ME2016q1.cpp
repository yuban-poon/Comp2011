#include <iostream>
using namespace std;

int count_unique_letters(const char text[]){
	int count = 0;
	for (int i = 0; i < 100; i++){
		bool isExist = false;
		for (int j = 0; j < i; j++){
			if (text[j] == text[i] || text[j] - 'a' + 'A' == text[i] || (text[j] - 'A' + 'a') == text[i]){
				isExist = true;
				break;
			}
		}
		if (!isExist){
			count++;
		}
		if (text[i] == '\0')
		{
			break;
		}
	}
	return count;
}

int main(){
	char text1[100] = "Today and tomorrow";
	cout << count_unique_letters(text1) << endl;

	char text2[100] = "Object-Oriented Programming";
	cout << count_unique_letters(text2) << endl;
}