#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double solveDiscriminat(double a, double b, double c);
double solveRootOne(double a, double b, double discriminant);
double solveRootTwo(double a, double b, double discriminant);
void solveQuadraticEquation(double a, double b, double c);
void CleanBuffer();

int main(void) {
    double a, b, c;

    /* Ask the user for input until 0 0 0 is entered */
    do {
        printf(" Enter coeficients a, b, and c: ");
        scanf("%lf %lf %lf", &a, &b, &c);

        /* First value must be higher than 0 */
        if (a == 0) {
            printf(" First value must be higher than 0!\n");
        } else {
            solveQuadraticEquation(a, b, c);
        }
    }
    while (a != 0 && b != 0 && c != 0);

    printf("\n");

    return EXIT_SUCCESS;
}

void solveQuadraticEquation(double a, double b, double c){
    double discriminant, root1, root2;

    discriminant = solveDiscriminat(a, b, c);

    if (discriminant < 0)
        printf(" No roots\n");
    else if (discriminant == 0){
        root1 = solveRootOne(a, b, discriminant);

        /* Do not print when inputting 0 0 0 */
        if (root1 == root1) {
            printf(" One root: %f\n", root1);
        } else {
            
        }
    } else {
        root1 = solveRootOne(a, b, discriminant);
        root2 = solveRootTwo(a, b, discriminant);

        if (root1 == root1  && root2 == root2) {
            printf(" Two roots: %f and %f\n", root1, root2);
        }
    }
}

double solveDiscriminat(double a, double b, double c) {
    return b * b - 4 * a * c;
}

double solveRootOne(double a, double b, double discriminant) {
    if (discriminant == 0) {
        return -b/(2*a);
    } else {
        return (-b + sqrt(discriminant))/(2*a);
    }
}

double solveRootTwo(double a, double b, double discriminant) {
    return (-b - sqrt(discriminant))/(2*a);
}
