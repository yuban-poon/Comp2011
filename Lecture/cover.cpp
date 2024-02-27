#include <iostream> /* File: swap.cpp */
using namespace std;
int main() /* To sort 2 numbers so that the 2nd one is larger */
{
	char small_y, big_y;
	cin >> small_y;							 // Character in small case
	big_y = small_y + 'A' - 'a'; // Character in big case
	cout << 'A' - 'a' << '\t' << small_y << '\t' << big_y << endl;
	
	float x = 3.2;	// Initialize x with 3.2 by assignment
	double y = 5.7; // Initialize y with 5.7 by assignment
	short k = x;		// k = ?
	int n;
	n = y; // n = ?
	cout << k << '\t' << n << endl;
	return 0;
}