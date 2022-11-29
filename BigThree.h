#include <iostream>
#include <vector>

using namespace std;

// store a digit between '0' and '2'
class BigThreeDigit {
    friend ostream &operator<<(ostream &, BigThreeDigit &);

public:

    // always initialize to 0
    BigThreeDigit(); // initialize to 0

    // initialize the digit, return error if the integer value is not between 0 and 2
    BigThreeDigit(int x);

    // initialize the digit, return error if the character is not '0', '1', '2'
    BigThreeDigit(char x);

    bool isZero();

    // add the current digit with d, return a new digit that store the value, plue whether there is a carry
    pair<BigThreeDigit, bool> add(BigThreeDigit d);

    // increment digit by one, return a new digit that store the value, plue whether there is a carry
    pair<BigThreeDigit, bool> incr();

    // subtract d from the current digit, return a new digit that store the value, plue whether there is a borrow necessary
    pair<BigThreeDigit, bool> sub(BigThreeDigit d);

    // decrement digit by one, return a new digit that store the value, plue whether there is a borrow necessary
    pair<BigThreeDigit, bool> decr();

    // multiply the current digit with d, return a new digit that store the value, plue whether there is a carry
    pair<BigThreeDigit, bool> multiply(BigThreeDigit d);


private:
    int c;
};


/*
#  storing a tenary number. Notice that the number are stored left to right
#  For example, for the number 10220
#  the vector actually stored  0-2-2-0-1
*/

class BigThree {
    friend ostream &operator<<(ostream &, BigThree &);

public:

    // Initialize a new number, set it to zero
    BigThree();

    // Convert a string into the number
    // Notice that the number is represented in the string in normal order
    // e.g. the number 10 should be represented as the string as "10"
    //      but will be stored in the vector as 0-1

    BigThree(string t);

    // copy constructor
    BigThree(const BigThree &bt);

    // assignement of bt to the current number.
    BigThree &operator=(BigThree &bt);

    // add the numebr bt to the current number, return a new number (current number not modified)
    BigThree operator+(BigThree &bt);

    // subtract the number bt to the current number, return a new number (current number not modified)
    // notice that it assume bt is smaller than the number
    // otherwise it will return an error and quit
    BigThree operator-(BigThree &bt);

    // remove the zeros at the front of the number (in this case at the end of the error
    // for example: 00121 becomes 121
    void RemoveFrontZeros();

    // Add n zeros to the right of the number
    // e.g. if number is 1010, then AddZero(3) will change the number to 1010000
    void AddZeros(int n);

    // add the numebr bt to the current number, return a new number (current number not modified)
    BigThree operator*(BigThreeDigit &d);

    pair<BigThree, BigThree> split(int d);

    // Methods you need to implement

    BigThree(long x);

    BigThree SimpleMultiply(BigThree &b);

    BigThree RecursiveMultiply(BigThree &b);

    BigThree FasterRecursiveMultiply(BigThree &b);

private:
    vector<BigThreeDigit> s;
};


