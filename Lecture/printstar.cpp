#include <iostream>
using namespace std;

int main()
{
	// Fat RAT
	int height;
	cout << "Please input the height of the rectangle: ";
	cin >> height;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j <= i; j++)
		{
			cout << "*";
		}
		cout << endl;
	}
	cout << endl;

	// Hollow RAT
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j <= i; j++)
		{
			if (i == 0 || i == height - 1 || j == 0 || j == i)
			{
				cout << "*";
			}
			else
			{
				cout << " ";
			}
		}
		cout << endl;
	}
	cout << endl;

	// Upside-down RAT
	for (int i = 0; i < height; i++)
	{
		for (int j = height; j > i; j--)
		{
			cout << "*";
		}
		cout << endl;
	}
	cout << endl;

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			if (j%5 <= i)
			{
				cout << "*";
			}else
			{
				cout << " ";
			}
		}
		cout << endl;
	}
	
}