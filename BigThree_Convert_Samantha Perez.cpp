#include <iostream>
#include <vector>
#include <cmath>
#include "BigThree.h"


BigThree convert_0_9(long x) {
    if ((x < 0) || (x > 9)) {
        cerr << "Only allow 0 - 9 to be converted" << endl;
        exit(0);
    }
    BigThree res;
    switch (x) {
        case 0: {
        }
            break;
        case 1: {
            BigThree r("1");
            res = r;
        }
            break;
        case 2: {
            BigThree r("2");
            res = r;
        }
            break;
        case 3: {
            BigThree r("10");
            res = r;
        }
            break;
        case 4: {
            BigThree r("11");
            res = r;
        }
            break;
        case 5: {
            BigThree r("12");
            res = r;
        }
            break;
        case 6: {
            BigThree r("20");
            res = r;
        }
            break;
        case 7: {
            BigThree r("21");
            res = r;
        }
            break;
        case 8: {
            BigThree r("22");
            res = r;
        }
            break;
        case 9: {
            BigThree r("100");
            res = r;
        }
            break;
    }

    return res;
}

BigThree::BigThree(long x) {
    if(x < 10){
        this -> s = convert_0_9(x).s;
        return;
    }
    if(x == 10){
        this -> s = {1,0,1};
        return;
    }

    long div = pow(10, ((1 + log10(x))/2));
    long mostSig = x/div;
    long leastSig = x%div;
    BigThree answerMostSig(mostSig);
    BigThree answerBuffer(div);
    BigThree answerLeastSig(leastSig);
    this -> s = (answerMostSig.SimpleMultiply(answerBuffer) + answerLeastSig).s;
}
