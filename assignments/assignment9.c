/* Name: Lucas Mørk Frendorf */
/* Group: B201 */
/* Ran using: gcc assignment9.c -ansi -Wall -pedantic && ./a.out && rm a.out */
/* Ran on: Linux [x86_64] */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Symbolic constants */

/* Prototypes */
int is_palindrome_itre(char *string);
int is_palindrome_rec(char *string, int start, int end);

int main(void) {
    char string[] = "regninger";

    printf(" Trying to find for string: %s\n", string);

    if (is_palindrome_itre(string)) {
        printf(" Found palindrome iterative\n");
    } else {
        printf(" Dind't find a palindrome iterative\n");
    }


    if (is_palindrome_rec(string, 0, strlen(string)-1)) {
        printf(" Found palindrome recursive\n");
    } else {
        printf(" Dind't find a palindrome recursive\n");
    }
    
    return EXIT_SUCCESS;
}

int is_palindrome_itre(char *string) {
    int mid, len, i;

    len = strlen(string);
    mid = len/2;

    for (i = 0;i <= mid;i++)
    {
        len--;

        if (string[i] != string[len]) {
            return 0;
        }
    }

    return 1;
}

int is_palindrome_rec(char *string, int start, int end) {
    if (start == end) {
        return 1;
    }

    if (string[start] == string[end]) {
        start++;
        end--;

        return is_palindrome_rec(string, start, end);
    } else {
        return 0;
    }

    return 1;
}