/* Name: Lucas Mørk Frendorf */
/* Group: B201 */
/* Ran using: gcc import_data.c -ansi -Wall -pedantic && ./a.out && rm a.out */
/* Ran on: Linux [x86_64] */
#include <stdio.h>
#include <stdlib.h>

/* Symbolic constants */
struct assignmentData {
    int date;
    int class;
    int time;
};

/* Prototypes */

int main(void) {
    int i;
    FILE* my_file = fopen("exampledata.csv", "r");
    struct assignmentData array[100];

    for (i = 0; i < sizeof(array)/sizeof(array[0]); ++i)
    {
        int got = fscanf(my_file, "%d,%d,%d", &array[i].date, &array[i].class, &array[i].time);
        if (got != 3) break;
    }
    fclose(my_file);


    /* TODO get length of array */
    for (i = 0; i < 3; ++i)
    {
        printf("%d | %d | %d\n", array[i].date, array[i].class, array[i].time);
    }
    
    return EXIT_SUCCESS;
}