/* Name: Lucas Mørk Frendorf */
/* Group: B201 */
/* Ran using: gcc workshop4.c -ansi -Wall -pedantic && ./a.out && rm a.out */
/* Ran on: Linux [x86_64] */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Symbolic constants */

/* Prototypes */
int isPrime(int x);
int isGCD(int x);
int isTwoModFive(int x);


int main(void) {
    int x = 2;

    for (x = 100000; x < 2000000; x++)
    {
        if ((isPrime(x) && !isTwoModFive(x)) || !(isPrime(x) || !isGCD(x) || isTwoModFive(x)) ||(!isPrime(x) && !isGCD(x) && isTwoModFive(x))) {
            printf("ay %d\n", x);
        }
    }

    /* printf("isPrime %d\n", isPrime(2));
    printf("isGCD %d\n", isGCD(1)); */
    

    return EXIT_SUCCESS;
}

int isPrime(int x) {
    int i;

    for (i = 2; i <= x / 2; ++i) {
        if (x % i == 0) {
            return 1;
        }
    }

    return 0;
}

int isGCD(int x) {
    int i, gcd;

    for(i=1; i <= x && i <= 2; ++i)
    {
        if(x%i == 0 && 2%i == 0)
            gcd = i;
    }

    if (gcd == 1)
        return 1;

    return 0;
}

int isTwoModFive(int x) {
    return (pow(9.0, (double) x) - 2%5) == 2;
}