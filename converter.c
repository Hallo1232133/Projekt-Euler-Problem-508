#include "stdlib.h"

// computes a = (-1 + i) ^ power
// returns R(a) und Im(a) in pointers
// makes use of the De Moivre's formula (a + bi)^x = \sqrt{a^2 + b^2}^x (\cos{\theta} + \sin{\theta})
// source/explanation: https://en.wikipedia.org/wiki/De_Moivre%27s_formula
void complexToPower(int power, __int128* real, __int128* imag) {
    // values for trigonometric functions for \theta = {0, 3/4 \pi, 1/2 \pi, 1/4 \pi}
    int cos[] = {1, 0, -1, 0};
    int sin[] = {0, -1, 0, 1};

    // compute (-1 + i) ^ tempPow, tempPow - the biggest even number with tempPow <= power 
    int tempPow = power;
    if (tempPow & 1) {
        --tempPow;
    }

    __int128 length = 1;

    // constant used
    length =  length << (tempPow >> 1);

    *real = length * cos[(tempPow & 7) >> 1];
    *imag = length * sin[(tempPow & 7) >> 1];

    // compute (-1 + i) ^tpower when power is not even
    if (power & 1) {
        // might be slower than when using temporary variables to store the results
        *imag = *real - *imag;
        *real = *imag - ((*real) << 1);
    }
}

// conversion done through representing the number as a sum of powers of (-1 + i)
void convertNumberToBasis(unsigned __int128 from, __int128* real, __int128* imag) {
    *real = 0;
    *imag = 0;
    __int128* currReal = (__int128*) malloc(sizeof (__int128));
    __int128* currImag = (__int128*) malloc(sizeof (__int128));
    
    int power = 0;
    while (from) {
        if (from & 1) {
            complexToPower(power, currReal, currImag);
            *real += *currReal; 
            *imag += *currImag;
        }

        from = from / 10;
        ++power;
    }

    free(currReal);
    free(currImag);
}

// algorithm taken from https://math.stackexchange.com/questions/1209190/base-conversion-how-to-convert-between-decimal-and-a-complex-base
unsigned __int128 to_bm1pi(__int128 real, __int128 imag) {
    unsigned __int128 result = 0;
    unsigned __int128 digit = 1;

    while (real || imag) {
        // might be slower than when using temporary variables to store the results
        if ((real + imag) & 1) {
            result += digit;
            real = (imag - real + 1) >> 1;
        }
        else {
            real = (imag - real) >> 1;
        }
        imag = (((real) << 1) - ((imag) << 1)) >> 1;

        digit *= 10;
    }    
    
    return result;
}