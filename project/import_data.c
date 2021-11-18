/* Name: Lucas Mørk Frendorf */
/* Group: B201 */
/* Ran using: gcc import_data.c -ansi -Wall -pedantic && ./a.out && rm a.out */
/* Ran on: Linux [x86_64] */
#include <stdio.h>
#include <stdlib.h>

/* Symbolic constants */
struct assignmentData {
    int date;
    int time;
    char class[50];
};

/* Prototypes */

int main(void) {
    int i, found;
    FILE* my_file = fopen("exampledata.csv", "r");
    struct assignmentData array[100];

    for (i = 0; i < sizeof(array)/sizeof(array[0]); ++i)
    {
        int found = fscanf(my_file, "%d,%d,%s", &array[i].date, &array[i].time, array[i].class);
        if (found != 3) break;
    }
    fclose(my_file);


    /* TODO get length of array */
    for (i = 0; i < 3; ++i)
    {
        printf("%d | %d | %s\n", array[i].date, array[i].time, array[i].class);
    }
    
    return EXIT_SUCCESS;
}