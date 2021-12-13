/* Name: Lucas Mørk Frendorf */
/* Group: B201 */
/* Ran using: gcc exam2.c -ansi -Wall -pedantic && ./a.out && rm a.out */
/* Ran on: Linux [x86_64] */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/* Symbolic constants */
#define MAX_ROUNDS 3
#define SINGELS_MIN_DICES 3
#define SINGLES_ROUNDS 6
#define BONUS_ROUNDS (SINGLES_ROUNDS + 1)
#define PAIR_ROUNDS (BONUS_ROUNDS + 2)
#define IDENTICAL_ROUNDS (PAIR_ROUNDS + 2)
#define SMALL_STRAIGHT_ROUNDS (IDENTICAL_ROUNDS + 1)
#define BIG_STRAIGHT_ROUNDS (SMALL_STRAIGHT_ROUNDS + 1)
#define HOUSE_ROUNDS (BIG_STRAIGHT_ROUNDS + 1)
#define CHANCE_ROUNDS (HOUSE_ROUNDS + 1)
#define YATZY_ROUNDS (CHANCE_ROUNDS + 1)

/* Dice faces */
#define DICE_MAX_FACE 6
#define DICE_MIN_FACE 1

/* Yatzy game rules */
#define SMALL_STRAIGHT_POINTS 15
#define SMALL_STRAIGHT_MIN 1
#define SMALL_STRAIGHT_MAX 5

#define BIG_STRAIGHT_POINTS 20
#define BIG_STRAIGHT_MIN 2
#define BIG_STRAIGHT_MAX 6

#define YATZY_POINTS 50
#define YATZY_MIN 1
#define YATZY_MAX 6

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
    int diceAmount = 0, game = 0, bonus = 0, total = 0, i;
    int *dice = (int*) calloc(diceAmount, sizeof(int));
    int scoreCard[14];
    char text[][YATZY_ROUNDS] = {"Ones", "Twos", "Threes", "Fours", "Fives", "Sixes", "Bonus", "One pair", "Two pair", "Three of a kind", "Four of a kind", "Small straight", "Big straight", "Full house", "Chance", "Yatzy"};
    
    printf(" Amount of dice (Min: 5): ");
    scanf(" %d", &diceAmount);

    if (diceAmount < 5) {
        printf("Please use 5 dices or more!\n");
        return;
    }

    printf("\n");

    /* Set the rand seed to time */
    srand(time(NULL));

    waitForUserInput();

    printf(" Welcome to Yatzy\n");
    printf(" Press (Enter) everytime you wanna progress in the game!\n");

    waitForUserInput();

    for (game = 0; game < YATZY_ROUNDS; game++)
    {
        if (game == BONUS_ROUNDS)
            continue;

        printf(" %s\n", text[game]);

        rollDice(dice, diceAmount);

        if (game < SINGLES_ROUNDS) {
            printf(" You got %d, %d's\n", dice[game], game+1);

            scoreCard[game] = dice[game] * (game+1);
            /* Implement bonus into our scorecard */
            bonus += scoreCard[game];
        } else if (game < PAIR_ROUNDS) {
            scoreCard[game] = getPairs(dice, diceAmount, game - 1 - PAIR_ROUNDS);
        } else if (game < IDENTICAL_ROUNDS) {
            scoreCard[game] = getKind(dice, diceAmount, game - IDENTICAL_ROUNDS - 3);
        } else if (game < SMALL_STRAIGHT_ROUNDS) {
            if (getStraight(dice, diceAmount, SMALL_STRAIGHT_MIN, SMALL_STRAIGHT_MAX)) {
                scoreCard[game] = SMALL_STRAIGHT_POINTS;
            } else {
                scoreCard[game] = 0;
            }
        } else if (game < BIG_STRAIGHT_ROUNDS) {
            if (getStraight(dice, diceAmount, BIG_STRAIGHT_MIN, BIG_STRAIGHT_MAX)) {
                scoreCard[game] = BIG_STRAIGHT_POINTS;
            } else {
                scoreCard[game] = 0;
            }
        } else if (game < HOUSE_ROUNDS) {
            scoreCard[game] = getHouse(dice, diceAmount);
        } else if (game < CHANCE_ROUNDS) {
            scoreCard[game] = getChance(dice, diceAmount);
        } else if (game < YATZY_ROUNDS) {
            /* TODO fix yatzy */
            if (getStraight(dice, diceAmount, YATZY_MIN, YATZY_MAX)) {
                scoreCard[game] = YATZY_POINTS;
            } else {
                scoreCard[game] = 0;
            }
        }

        printf(" Points this round: %d\n", scoreCard[game]);

        waitForUserInput();
    }

    for (i = 0; i < YATZY_ROUNDS; i++)
    {
        printf("%15s | %d\n", text[i], scoreCard[i]);

        total += scoreCard[i];

        if (i == SINGLES_ROUNDS-1) {
            if (bonus < 63) {
                bonus = 0;
            }

            scoreCard[i] += bonus;

            printf("%15s | %d \n", "Bonus", bonus);
        }
    }

    printf("%15s | %d\n", "Total", total);

    printf(" Press (Enter) to start a new game\n");
    waitForUserInput();

    startYatzy();
}

void rollDice(int *dice, int diceAmount) {
    int i, roll;

    printf(" Rolled:");

    for (i = 0; i <= diceAmount; i++)
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
            printf(" Found %d of a kind in %d's\n", kindAmount, i);
            return i * kindAmount;
        }
    }

    printf(" Didn't find %d of a kind\n", kindAmount);

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

                printf(" Found a pair of %d's\n", i);

                pairsAmount--;

                if (pairsAmount <= 0) {
                    break;
                }
            }
        }

        if (pairsAmount == 1) {
            printf(" Didn't find last pair\n");
            result = 0;
            break;
        } else {
            pairsAmount--;
        }
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