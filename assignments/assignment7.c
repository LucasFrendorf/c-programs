/* Ran using: gcc assignment7.c -ansi -Wall -pedantic -lm && ./a.out && rm a.out */
/* -lm is due to math.h on linux */
/* Ran on: Linux [x86_64] */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Prototypes */
void trap(double a, double b, double n, double func(double x));
double f1(double x);
double f2(double x);

int main(void) {
    int i;

    printf(" Trap of function: x^2 * sin(x)\n");
    for(i = 2; i <= 128; i *= 2)
	{
        trap(0, 3.14159, i, f1);
    }

    printf("\n Trap of function: sqrt(4 - x^2)\n");
    for(i = 2; i <= 128; i *= 2)
	{
        trap(-2, 2, i, f2);
    }
    
    return EXIT_SUCCESS;
}


void trap(double a, double b, double n, double f(double)) {
    double h, T, e = 0, aTemp = a;
    int i;
    
    h = (b-a)/n;

    for (i = 0; i < n; i++)
    {
        aTemp += h;
        e += f(aTemp);
    }

    T = (h/2) * (f(a) + f(b) + (2*e));
    printf(" Trap is: %f\n", T);
}

double f1(double x) {
    return pow(x, 2) * sin(x);
}

double f2(double x) {
    return sqrt(4 - pow(x, 2));
}