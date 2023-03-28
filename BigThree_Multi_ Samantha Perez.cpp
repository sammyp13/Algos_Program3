#include <iostream>
#include <vector>
#include "BigThree.h"

BigThree BigThree::SimpleMultiply(BigThree &c) {
    BigThree b = c;
    BigThree answer;
    for (int i = 0; i < s.size(); i++) {
        if (s[i].isZero()) {
            b.AddZeros(1);
        } else if (s[i].decr().first.isZero()) {
            BigThree temp = b + answer;
            answer = temp;
            b.AddZeros(1);
        } else {
            BigThree temp1 = b + answer;
            BigThree temp2 = temp1 + b;
            answer = temp2;
            b.AddZeros(1);
        }
    }
    return answer;
}

BigThree BigThree::RecursiveMultiply(BigThree &b) {
    if (this->s.size() == 1) {
        if (this->s[0].isZero()) {
            return 0;
        } else if (this->s[0].decr().first.isZero()) {
            return b;
        } else {
            return b + b;
        }
    }
    if (b.s.size() == 1) {
        if (b.s[0].isZero()) {
            return 0;
        } else if (b.s[0].decr().first.isZero()) {
            return *this;
        } else {
            return *this + *this;
        }
    }

    //split a and b until they are single digits
    size_t n = this -> s.size();
    size_t m = b.s.size();
    size_t halfASize = n/2;
    size_t halfBSize = m/2;
    BigThree aFirst, aInner, bOuter, bLast;
    aFirst.s = vector <BigThreeDigit> (this -> s.begin() + halfASize, this -> s.end());
    aInner.s = vector <BigThreeDigit> (this -> s.begin(), this -> s.begin() + halfASize);
    bOuter.s = vector <BigThreeDigit> (b.s.begin() + halfBSize, b.s.end());
    bLast.s = vector <BigThreeDigit> (b.s.begin(), b.s.begin() + halfBSize);

    //FOIL multiply a and b
    //(a+b)(c+d) -> (first + inner)(outer + last)
    BigThree firstOuter = aFirst.RecursiveMultiply(bOuter);
    firstOuter.s.insert(firstOuter.s.begin(), halfASize + halfBSize, 0);

    BigThree firstLast = aFirst.RecursiveMultiply(bLast);
    firstLast.s.insert(firstLast.s.begin(), halfASize, 0);

    BigThree innerOuter = aInner.RecursiveMultiply(bOuter);
    innerOuter.s.insert(innerOuter.s.begin(), halfBSize, 0);

    BigThree innerLast = aInner.RecursiveMultiply(bLast);

    return firstOuter + firstLast + innerOuter + innerLast;
}

BigThree BigThree::FasterRecursiveMultiply(BigThree &b) {
    if (this->s.size() == 1) {
        if (this->s[0].isZero()) {
            return 0;
        } else if (this->s[0].decr().first.isZero()) {
            return b;
        } else {
            return b + b;
        }
    }
    if (b.s.size() == 1) {
        if (b.s[0].isZero()) {
            return 0;
        } else if (b.s[0].decr().first.isZero()) {
            return *this;
        } else {
            return *this + *this;
        }
    }

    //split a and b until they are single digits
    size_t n = this -> s.size();
    size_t m = b.s.size();
    size_t halfSize = std::min(n/2, m/2);
    BigThree aFirst, aInner, bOuter, bLast;
    aFirst.s = vector <BigThreeDigit> (this -> s.begin() + halfSize, this -> s.end());
    aInner.s = vector <BigThreeDigit> (this -> s.begin(), this -> s.begin() + halfSize);
    bOuter.s = vector <BigThreeDigit> (b.s.begin() + halfSize, b.s.end());
    bLast.s = vector <BigThreeDigit> (b.s.begin(), b.s.begin() + halfSize);

    BigThree firstOuter = aFirst.FasterRecursiveMultiply(bOuter);
    BigThree innerLast = aInner.FasterRecursiveMultiply(bLast);
    BigThree addFirstInner = aFirst + aInner;
    BigThree addOuterLast = bOuter + bLast;
    BigThree addAll = addFirstInner.FasterRecursiveMultiply(addOuterLast);
    BigThree foil = firstOuter + innerLast;
    BigThree addFoil = addAll - foil;
    firstOuter.s.insert(firstOuter.s.begin(), 2 * halfSize, 0);
    addFoil.s.insert(addFoil.s.begin(), halfSize, 0);

    return firstOuter + addFoil + innerLast;
}

