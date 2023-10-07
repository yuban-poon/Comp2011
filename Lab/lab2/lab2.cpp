#include <iostream>
using namespace std;

int main() {
    int number1, number2; // Both inputs will be positive integers, but you do not know which is larger
    int small, large; // small should be the smaller of the two numbers, large should be the larger
    int finalScore = 0; // The final score of the game

    // Get the range from the user
    cin >> number1 >> number2;

    /* Please do not change the code above this line */ 

    // Task 1 - Find the small and large bounds of the range
    ///////////////////
    // Your Code Here //
    small = (number1 > number2) ? number2: number1;
    large = (number1 > number2) ? number1: number2;
    ///////////////////

    // Task 2 - Find the perfect numbers in the range and update the final score
    ///////////////////
    // Your Code Here //
    for (int i = small; i <= large; i++)
    {
        // code //
        // check perfect number
        int sumOfAllCd = 0;
        for (int j = 1; j <= i/2; j++)
        {
            //find all common divisors of i and add it to sumOfCd
            if(i%j == 0) {
                sumOfAllCd += j;
            }
        }
        //check sum of all common divisors is equal to current number (1+2+3=6)
        (sumOfAllCd == i) ? finalScore += i : finalScore -= i;
    }
    ///////////////////


    /* Please do not change the code below this line */

    cout << finalScore;
    return 0;
}