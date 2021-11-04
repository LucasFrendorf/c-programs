/* Name: Lucas Mørk Frendorf */
/* Group: B201 */

/* Ran using: gcc exam2.c -ansi -Wall -pedantic && ./a.out && rm a.out */
/* Ran on: Linux [x86_64] */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

/* Symbolic constants */
#define MAX_ROUNDS 3
#define SINGELS_MIN_DICES 3
#define SINGLES_ROUNDS 6
#define PAIR_ROUNDS SINGLES_ROUNDS + 2
#define IDENTICAL_ROUNDS PAIR_ROUNDS + 2
#define SMALL_STRAIGHT_ROUNDS IDENTICAL_ROUNDS + 1
#define BIG_STRAIGHT_ROUNDS SMALL_STRAIGHT_ROUNDS + 1
#define HOUSE_ROUNDS BIG_STRAIGHT_ROUNDS + 1
#define CHANCE_ROUNDS HOUSE_ROUNDS + 1
#define YATZY_ROUNDS CHANCE_ROUNDS + 1

/* #define NUM_TO_TEXT ["one", "two", "three", "four", "five", "six"] */

/* Prototypes */
void rollDice(int *dice, int amount);
int getAllSameFace(int face, int *dice, int diceAmount);
void waitForUserInput();

int main(void) {
    int diceAmount = 10, game = 0, i, amount;
    int *dice = (int*)malloc((diceAmount+10) * sizeof(int));
    int scoreCard[14]; 

    /* Set the rand seed to time */
    srand(time(NULL));

    printf(" Welcome to Yatzy\n");
    printf(" Press (Enter) everytime you wanna progress in the game!\n");

    waitForUserInput();

    for (game = 0; game < 15; game++)
    {
        printf(" Rolling dice for game: %d\n", game);

        rollDice(dice, diceAmount);

        printf(" You rolled:");

        for (i = 0; i <= diceAmount; i++)
        {
            printf(" %d ", dice[i]);
        }

        printf("\n");

        /* Singles */
        if (game < SINGLES_ROUNDS) {
            amount = getAllSameFace(game+1, dice, diceAmount);

            printf(" You got %d, %d's\n", amount, game+1);

            /* TODO Find out what the rules are ??!!?!?! */
            if (amount > SINGELS_MIN_DICES) {
                scoreCard[game] = amount * (game+1);
            } else {
                scoreCard[game] = 0;
            }
        } else if (game < PAIR_ROUNDS) {
            printf("Pair round %d\n", game);
        } else if (game < IDENTICAL_ROUNDS) {
            printf("Identical round %d\n", game);
        } else if (game < SMALL_STRAIGHT_ROUNDS) {
            printf("Small stright round %d\n", game);
        } else if (game < BIG_STRAIGHT_ROUNDS) {
            printf("Big stright round %d\n", game);
        } else if (game < HOUSE_ROUNDS) {
            printf("House round %d\n", game);
        } else if (game < CHANCE_ROUNDS) {
            printf("Chance round %d\n", game);
        } else if (game < YATZY_ROUNDS) {
            printf("Yatzy round %d\n", game);
        } else {
            
        }

        scoreCard[game] = 0;

        printf(" Points this round: %d\n", scoreCard[game]);

        waitForUserInput();
    }

    printf(" Exiting!\n");

    return EXIT_SUCCESS;
}

void rollDice(int *dice, int diceAmount) {
    int i;

    for (i = 0; i <= diceAmount; i++)
    {
        dice[i] = rand()%6 + 1;
    }
}


int getAllSameFace(int face, int *dice, int diceAmount) {
    int i, count = 0;

    for (i = 0; i <= diceAmount; i++)
    {
        if (dice[i] == face)
            count++;
    }

    return count;
}

/* int getAllPairs(int *dice, int diceAmount) {
    int i, count = 0;

    for (i = 0; i <= diceAmount; i++)
    {

    }
} */

void waitForUserInput() {
    getchar();
}
