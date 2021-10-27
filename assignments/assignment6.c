/* Ran using: gcc assignment6.c -ansi -Wall -pedantic && ./a.out && rm a.out */
/* Ran on: Linux [x86_64] */
#include <stdio.h>
#include <stdlib.h>

/* Symbolic constants */
#define TALBE1_SIZE 7
#define TALBE2_SIZE 5
#define MAX_TABLE_SIZE TALBE1_SIZE + TALBE2_SIZE

/* Prototypes */
double* combineTable(double table1[], int size1, double table2[], int size2);

int main(void) {
    int i;
    double *result;
    double table1[TALBE1_SIZE] = {-7.0, 1.0, 4.0, 5.0, 57.0, 75.0, 80.0};
    double table2[TALBE2_SIZE] = {-5.0, 1.0, 3.0, 5.0, 55.0};

    result = combineTable(table1, TALBE1_SIZE, table2, TALBE2_SIZE);

    printf(" Combined table: ");

    for(i = 0; i < MAX_TABLE_SIZE; i++)
        printf("%f ", result[i]);

    printf("\n");

    return EXIT_SUCCESS;
}

double* combineTable(double table1[], int size1, double table2[], int size2) {
    int i, lSize, sSize, pos = 0;
    double *lTable, *sTable;
    static double outputTable[MAX_TABLE_SIZE];

    /* Determine what array is the longest */
    lSize = size1 > size2 ? size1 : size2;
    lTable = size1 > size2 ? table1 : table2;

    sSize = size1 > size2 ? size2 : size1;
    sTable = size1 > size2 ? table2 : table1;

    /* iterate through the longest array */
    for (i = 0; i < lSize; i++)
    {
        /* Also iterate through the small array until size has been reached */
        if (i >= sSize) {
            outputTable[pos] = lTable[i];
            pos++;
        } else {
            if (lTable[i] == sTable[i]) {
                outputTable[pos] = lTable[i];
                pos++;
            } else {
                /* Favor small values or larger */
                outputTable[pos] = lTable[i] > sTable[i] ? sTable[i] : lTable[i];
                pos++;

                outputTable[pos] = lTable[i] > sTable[i] ? lTable[i] : sTable[i];
                pos++;
            }
        }
    }

    return outputTable;
}