#include <iostream>
using namespace std;

int main()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if ((i + j) % 2)
				continue;
			cout << i + j << "_";
		}
	}
}