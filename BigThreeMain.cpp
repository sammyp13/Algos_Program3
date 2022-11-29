#include <iostream>
#include "BigThree.h"


int main() {
    string q, q1;
    cin >> q;
    cin >> q1;
    BigThree b(q);
    BigThree b1(q1);
    BigThree b4(q);
    BigThreeDigit zero, one(1), two(2);

    cout << "First number : " << " " << b << endl;
    cout << "Second number : " << " " << b1 << endl;
    BigThree b2 = b + b1;
    cout << "Sum  : " << b2 << endl;
    BigThree b3 = b - b1;
    cout << "Diff : " << b3 << endl;
    b4.AddZeros(3);
    cout << "shift 3 for first number : " << b4 << endl;

    BigThree c1 = b1 * zero;
    BigThree c2 = b1 * one;
    BigThree c3 = b1 * two;

    cout << "Multiply second number with 0, 1, 2 : " << c1 << " " << c2 << "  " << c3 << endl;
    pair<BigThree, BigThree> s = c3.split(2);
    cout << "Split (2 * second number) with 2 digit on the right number : " << s.first << " " << s.second << endl;

    BigThree m1 = b1.SimpleMultiply(b);
    BigThree m2 = b1.RecursiveMultiply(b);
    BigThree m3 = b1.FasterRecursiveMultiply(b);
    cout << "Multiply b and b1 (simple) : " << m1 << endl;
    cout << "Multiply b and b1 (recursive) : " << m2 << endl;
    cout << "Multiply b and b1 (faster recursive) : " << m3 << endl;

    BigThree conv(1372);
    cout << "Convert 1372 to ternary " << conv << endl;
}

