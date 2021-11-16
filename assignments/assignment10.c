/* Name: Lucas Mørk Frendorf */
/* Group: B201 */
/* Ran using: gcc assignment10.c -ansi -Wall -pedantic && ./a.out && rm a.out */
/* Ran on: Linux [x86_64] */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Symbolic constants */
char suitNames[4][4] = {"♣", "♦", "♥", "♠"};
char faceNames[5][6] = {"Jack", "Queen", "King", "Ace", "Joker"};

struct cards {
    int cardFace;
    int cardSuit;
};
typedef struct cards cards;

#define SUITS 4
#define FACES 13
#define JOKERS 3
#define CARDS_MAX SUITS*FACES + JOKERS

/* Prototypes */
void printDeck(cards *array, int arrayLen);
void shuffleCards(cards *array, int n);
int sortCards(const void *a, const void *b);

int main(void) {
    int suit, face, joker, count = 0;
    cards deck[CARDS_MAX];

    /* Random seed used in shuffling cards */
    srand(time(NULL));

    /* Adding all the cards to the deck */
    for (suit = 0; suit < SUITS; suit++)
    {
        for (face = 0; face < FACES; face++)
        {
            deck[count].cardFace = face;
            deck[count].cardSuit = suit;
            count++;
        }
    }

    /* Assignment says not to set face or suit for joker
    But it would just result in a lot of pointless if statements
    So decided not to */
    for (joker = 0; joker < JOKERS; joker++)
    {
        deck[count].cardFace = 13;
        deck[count].cardSuit = 3;
        count++;
    }

    printf(" -- Generated card deck --\n");
    printDeck(deck, CARDS_MAX);

    shuffleCards(deck, CARDS_MAX);

    printf(" -- Shuffled card deck --\n");
    printDeck(deck, CARDS_MAX);

    qsort(deck, CARDS_MAX, sizeof(cards), sortCards);

    printf(" -- Sorted card deck --\n");
    printDeck(deck, CARDS_MAX);

    return EXIT_SUCCESS;
}

void printDeck(cards *array, int arrayLen) {
    int i;

    for (i = 0; i < arrayLen; i++)
    {
        /* Adding +2 since our array starts at 0 and cards starts at 2 */
        if (array[i].cardFace == FACES) {
            printf(" Joker");
        } else if (array[i].cardFace+2 > 10) {
            printf(" %s of %s", faceNames[array[i].cardFace+2-11], suitNames[array[i].cardSuit]);
        } else {
            printf(" %d of %s", array[i].cardFace+2, suitNames[array[i].cardSuit]);
        }

        if (((i+1)%FACES == 0 && i != 0) || i == arrayLen-1) {
            printf("\n");
        } else {
            printf(" |");
        }
    }

    printf("\n");
}

void shuffleCards(cards *array, int n) {
    int i, j;
    cards temp;
    
    /* Shuffle deck using Fisher–Yates shuffle Algorithm */
    for (i = 0; i < n - 1; i++) 
    {
        j = rand() % (i+1);
        temp = array[j];

        array[j] = array[i];
        array[i] = temp;
    }
}

int sortCards(const void *a, const void *b) {
    cards *A = (cards *)a;
    cards *B = (cards *)b;

    /* First sort by suit if they are not equal */
    if (A->cardSuit != B->cardSuit)
        return A->cardSuit - B->cardSuit;

    /* Sort by face */
    return A->cardFace - B->cardFace;
}