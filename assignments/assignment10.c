/* Name: Lucas Mørk Frendorf */
/* Group: B201 */
/* Ran using: gcc assignment10.c -ansi -Wall -pedantic && ./a.out && rm a.out */
/* Ran on: Linux [x86_64] */
#include <stdio.h>
#include <stdlib.h>

/* Symbolic constants */
/* enum cardSuit {club, diamond, heart, spade};
typedef enum cardSuit cardSuit; */

struct cards {
    int cardFace;
    int cardSuit;
};
typedef struct cards cards;

#define SUITS 4;
#define FACES 14;

/* Prototypes */

int main(void) {
    int suit, face;

    for (suit = 1; suit <= SUITS; suit++)
    {
        printf("%d\n", suit);
        for (face = 1; face < FACES; face++)
        {
            
        }
    }

    return EXIT_SUCCESS;
}