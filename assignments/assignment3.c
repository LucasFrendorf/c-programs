#include <stdio.h>
#include <stdlib.h>

int main()
{
    int  num1, num2, i, gcd;

    printf("Enter two positive integers: ");
    scanf("%d %d", &num1, &num2);

    for(i=1; i <= num1 && i <= num2; ++i)
    {
        /* Checks if divided with i num1 & num2 return a whole number */
        if(num1%i == 0 && num2%i == 0)
            gcd = i;
    }

    printf("GCD of %d and %d is %d\n\n", num1, num2, gcd);

    return EXIT_SUCCESS;
}