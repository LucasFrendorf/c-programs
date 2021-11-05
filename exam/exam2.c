/* Name: Lucas Mørk Frendorf */
/* Group: B201 */

/* Ran using: gcc exam2other.c -ansi -Wall -pedantic && ./a.out && rm a.out */
/* Ran on: Linux [x86_64] */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

/* Dice faces */
#define DICE_MAX_FACE 6
#define DICE_MIN_FACE 1

/* Yatzy game rules */
#define SMALL_STRAIGHT_MIN 1
#define SMALL_STRAIGHT_MAX 5

#define BIG_STRAIGHT_MIN 2
#define BIG_STRAIGHT_MAX 6

#define YATZY_STRAIGHT_MIN 1
#define YATZY_STRAIGHT_MAX 6

#define CHANCE_DICES 5

/* Prototypes */
void startYatzy();
void rollDice(int *dice, int amount);
int getStraight(int *dice, int diceAmount, int minFace, int maxFace);
int getKind(int *dice, int diceAmount, int kindAmount);
int getPairs(int *dice, int diceAmount, int pairsAmount);
int getHouse(int *dice, int diceAmount);
int getChance(int *dice, int diceAmount);
void waitForUserInput();

int main(void) {
    startYatzy();

    return EXIT_SUCCESS;
}

void startYatzy() {
    int diceAmount = 5, game = 0, i, result;
    int *dice = (int*) calloc(diceAmount, sizeof(int));
    int scoreCard[14];
    char text[][16] = {"Ones", "Twos", "Threes", "Fours", "Fives", "Sixes", "One pair", "Two pair", "Three of a kind", "Four of a kind", "Small straight", "Big straight", "Full house", "Chance", "Yatzy"};
    
    printf("Amount of dices (Min: 5): ");
    scanf(" %d", &diceAmount);

    if (diceAmount < 5) {
        printf("Please use 5 dices or more!\n");
        return;
    }

    /* Set the rand seed to time */
    srand(time(NULL));

    printf(" Welcome to Yatzy\n");
    printf(" Press (Enter) everytime you wanna progress in the game!\n");

    waitForUserInput();

    for (game = 0; game < 15; game++)
    {
        printf(" %s\n", text[game]);

        rollDice(dice, diceAmount);

        if (game < SINGLES_ROUNDS) {
            result = dice[game];

            printf(" You got %d, %d's\n", result, game+1);

            /* Rules says to only get points if there is more than 3 of the same */
            if (result >= SINGELS_MIN_DICES) {
                /* Rules says to multiply sum with amount different from normal yatze rules */
                scoreCard[game] = result * (game+1);
            } else {
                scoreCard[game] = 0;
            }
        } else if (game < PAIR_ROUNDS) {
            scoreCard[game] = getPairs(dice, diceAmount, game - PAIR_ROUNDS);
        } else if (game < IDENTICAL_ROUNDS) {
            scoreCard[game] = getKind(dice, diceAmount, game - IDENTICAL_ROUNDS - 3);
        } else if (game < SMALL_STRAIGHT_ROUNDS) {
            if (getStraight(dice, diceAmount, SMALL_STRAIGHT_MIN, SMALL_STRAIGHT_MAX)) {
                scoreCard[game] = 15;
            } else {
                scoreCard[game] = 0;
            }
        } else if (game < BIG_STRAIGHT_ROUNDS) {
            if (getStraight(dice, diceAmount, 2, 6)) {
                scoreCard[game] = 20;
            } else {
                scoreCard[game] = 0;
            }
        } else if (game < HOUSE_ROUNDS) {
            scoreCard[game] = getHouse(dice, diceAmount);
        } else if (game < CHANCE_ROUNDS) {
            scoreCard[game] = getChance(dice, diceAmount);
        } else if (game < YATZY_ROUNDS) {
            if (getStraight(dice, diceAmount, YATZY_STRAIGHT_MIN, YATZY_STRAIGHT_MAX)) {
                scoreCard[game] = 50;
            } else {
                scoreCard[game] = 0;
            }
        }


        printf(" Points this round: %d\n", scoreCard[game]);

        waitForUserInput();
    }

    for (i = 0; i < 14; i++)
    {
        printf(" Got %d point(s) for game %s\n", scoreCard[i], text[i]);
    }

    printf(" Press (Enter) to start a new game\n");
    waitForUserInput();

    startYatzy();
}

void rollDice(int *dice, int diceAmount) {
    int i, roll;

    printf(" You rolled:");

    for (i = 0; i < diceAmount; i++)
    {
        dice[i] = 0;
    }
    
    for (i = 0; i < diceAmount; i++)
    {
        roll = rand()%DICE_MAX_FACE + 1;
        dice[roll-1] += 1;
        printf(" %d", roll);
    }

    printf("\n");
}


int getKind(int *dice, int diceAmount, int kindAmount) {
    int i;

    for (i = DICE_MAX_FACE; i >= DICE_MIN_FACE; i--) {
        if (dice[i-1] >= kindAmount) {

            return i * kindAmount;
        }
    }

    return 0;
}

/* Also used for yatzee */
int getStraight(int *dice, int diceAmount, int minFace, int maxFace) {
    int i;

    for (i = minFace;i <= maxFace;i++)
    {
        if (dice[i-1] == 0) {
            return 0;
        }
    }

    return 1;
}

int getPairs(int *dice, int diceAmount, int pairsAmount) {
    int i, result = 0;
 
    /* Go from the highest dice face and find if there is 2 or more of them */
    while (pairsAmount > 0) {
        for (i = DICE_MAX_FACE; i >= DICE_MIN_FACE; i--) {
            if (dice[i-1] >= 2) {
                result += i * 2;
                dice[i-1] -= 2;

                pairsAmount--;

                break;
            }
        }

        pairsAmount--;
    }

    return result;
}

int getHouse(int *dice, int diceAmount) {
    int i, result = 0;

    for (i = DICE_MAX_FACE; i >= DICE_MIN_FACE; i--) {
        if (dice[i-1] >= 3) {
            result += i * 3;
            dice[i-1] -= 3;

            break;
        }
    }

    if (result < 1)
        return 0;

    for (i = DICE_MAX_FACE; i >= DICE_MIN_FACE; i--) {
        if (dice[i-1] >= 2) {
            result += i * 2;

            return result;
        }
    }

    return 0;
}

int getChance(int *dice, int diceAmount) {
    int i, d, count = 0, result = 0;

    for (i = DICE_MAX_FACE; i >= DICE_MIN_FACE; i--) {
        if (dice[i-1] > 0) {
            for (d = 0; d < dice[i-1]; d++) {
                result += i;
                count++;

                if (count > 4) {
                    return result;
                }
            }
            
        }
    }

    return 0;
}

void waitForUserInput() {
    getchar();
}