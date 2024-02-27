#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;
int main()
{
	srand(time(0));
	int win = rand() % 100 + 1;
	int guess = 0;
	int player = 1;
	int low = 1, high = 100;
	while (true)
	{
		cout << "Player " << player << ", please enter your guess:" << endl;
		cin >> guess;
		while (guess < low || guess > high)
		{
			cout << "Invalid input, please enter a number between "
					 << low << " and " << high << endl;
			cin >> guess;
		}
		
		if (guess > win)
		{
			cout << "Sorry, the number is smaller than " << guess << endl;
			high = guess - 1;
		}
		else if (guess < win)
		{
			cout << "Sorry, the number is bigger than " << guess << endl;
			low = guess + 1;
		}
		else
		{
			cout << "Player " << player << ", you win!!!" << endl;
			break;
		}
		player = player == 1 ? 2 : 1;
	}
	return 0;
}
