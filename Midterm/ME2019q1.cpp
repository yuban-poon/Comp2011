#include <iostream>
using namespace std;

int main() {
  int num = 1;
	while (true)
	{
		++num;
		if (num == 8)
		{
			break;
		}

		if (!(num % 3))
		{
			continue;
		}

		if (num % 2)
		{
			num -= 3;
		}
		else
		{
			num += 3;
		}
		cout << num << " ";
	}
	cout << endl;
  return 0;
}