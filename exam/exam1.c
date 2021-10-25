/* Ran using: gcc exam1.c -ansi -Wall -pedantic -lm && ./a.out && rm a.out */
/* -lm is due to math.h on linux */
/* Ran on: Linux [x86_64] */

/* Libraries */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* Symbolic constants */
#define ADDITION '+'
#define SUBTRACTION '-'
#define MULTIPLICATION '*'
#define DIVISION '/'
#define POWER '^'
#define SQUAREROOT '#'
#define FLIP '%'
#define DIVIDE1 '!'
#define QUIT 'q'

/* Prototypes */
void scan_data(char *operator, double *input);
int is_non_binary(char *operator);
void do_next_op(char *operator, double *input, double **accumulator);
double run_calculator(double *accumulator);

int main(void) {
    double accumulator = 0.0;

    run_calculator(&accumulator);

    return EXIT_SUCCESS;
}

double run_calculator(double *accumulator) {
    char operator;
    double input;
    
    do {
        printf(" Enter operator, and an optional operand: ");
        scan_data(&operator, &input);

        do_next_op(&operator, &input, &accumulator);

        if (operator != QUIT) 
            printf(" Result so far is %f\n", *accumulator);
        else
            printf(" Final result is: %f\n", *accumulator);
    } while (operator != QUIT);

    return *accumulator;
}

void scan_data(char *operator, double *input) {
    scanf(" %c", &*operator);

    /* Only checks for value if it's need by the operator */
    if (is_non_binary(operator))
        scanf(" %lf", &*input);
}

int is_non_binary(char *operator) {
    if (*operator != SQUAREROOT && *operator != FLIP && *operator != DIVIDE1 && *operator != QUIT) {
        return 1;
    }

    return 0;
}

void do_next_op(char *operator, double *input, double **accumulator) {
    switch (*operator) {
        case ADDITION:
            **accumulator += *input;
            break;

        case SUBTRACTION:
            **accumulator -= *input;
            break;
        
        case MULTIPLICATION:
            **accumulator *= *input;
            break;

        case DIVISION:
            /* Don't allow doing the squareroot of 0 */
            if (*input == 0)
                break;

            **accumulator /= *input;
            break;
        
        case POWER:
            **accumulator = pow(**accumulator, *input);
            break;

        case SQUAREROOT:
            /* Don't allow using negative number with squareroot */
            if (**accumulator < 0)
                break;

            **accumulator = sqrt(**accumulator);
            break;

        case FLIP:
            **accumulator = -**accumulator;
            break;

        case DIVIDE1:
            /* Don't allow dividing by 0 */
            if (**accumulator == 0)
                break;

            **accumulator = **accumulator/1;
            break;
        
        default:
            break;
    }
}