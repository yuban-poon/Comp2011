#include <iostream>
using namespace std;

int main()
{
	// sum will be assign a romdom value
	int sum;
	int x;
	while (cin >> x)
		sum += x;
	cout << sum << endl;

	// j will be assign a romdom value
	int j;
	while (j < 10)
	{
		cout << "hello again!" << endl;
		j++;
	}

	int j = 0;
	while (j < 10);// ; is a null statement
	{
		cout << "hello again!" << endl;
		j++;
	}
	return 0;
}