/* Name: Lucas Mørk Frendorf */
/* Group: B201 */
/* Ran using: gcc exam3.c -ansi -Wall -pedantic && ./a.out && rm a.out */
/* Ran on: Linux [x86_64] */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Symbolic constants */
#define WON_POINTS 3
#define DRAW_POINTS 1

/* Array size initalizer for team array should be > 1 */
#define ARRAYSTARTSIZE 2 

typedef struct
{
    char teamName[4];
    int points;
    int goalsByTeam;
    int goalsOnTeam;
} team;

typedef struct
{
    char teamName[4];
    int points;
    int goalsByTeam;
    int goalsOnTeam;
    struct teamTest *nextTeam;
} teamTest;

typedef struct
{
    char day[4];
    char date[6];
    char clock[6];

    char team1Name[4];
    char team2Name[4];

    int team1Score;
    int team2Score;

    int spectators;
} game;

/* Prototypes */
int compareMatch(const void *a, const void *b);
int hash(unsigned char *str);

int main(void) {
    game *Games;
    team *Teams;
    teamTest *TeamsHash;
    int i, j, arrSize = ARRAYSTARTSIZE, lines = 0, count = 0, add = 0;
    char team1[4], team2[4];
    int hashNum;
    FILE *fp;

    if ((fp = fopen("kampe-2020-2021.txt","r")) == NULL){
        printf("Error! opening file");

        return EXIT_FAILURE;
    }

    /* Get the amount of games in our files and get teams */
    while(fscanf(fp, "%*s %*s %*s %s - %s %*i - %*i %*i", team1, team2) != EOF)
    {
        if (count == 0) {
            Teams = (team *) calloc(arrSize, sizeof(team));

            strcpy(Teams[count].teamName, team1);
            count++;
        } else {
            for (i = 0; i < count; i++)
            {
                if (strcmp(Teams[i].teamName, team1) == 0) {
                    add = 0;
                    break;
                }

                add = 1;
            }

            if (add == 1) {
                /* Allocating to the power of 2 for more efficiency so we dont have to realloc each time our size increases */
                if (count >= arrSize) {
                    arrSize *= arrSize;

                    Teams = realloc(Teams, arrSize * sizeof(team));
                }

                strcpy(Teams[count].teamName, team1);
                count++;

                add = 0;
            }
        }
        
        lines++;
    }

    /* Realloc teams to the correct size */
    Teams = (team *) realloc(Teams, sizeof(team) * (count-1));
    Games = (game *) malloc(sizeof(game) * lines);

    /* Go back to the first line again to load in the games array */
    fseek(fp, 0, SEEK_SET );

    for (i = 0; i < lines; i++)
    {
        fscanf(fp, "%s %s %s %s - %s %i - %i %i", Games[i].day, Games[i].date, Games[i].clock, Games[i].team1Name, Games[i].team2Name, &Games[i].team1Score, &Games[i].team2Score, &Games[i].spectators);

        /* printf("%d\n", count); */
        for (j = 0; j < count; j++)
        {
            /* Realloc doesn't initalize to 0 so we have to do it here */
            if (i == 0) {
                Teams[j].points = 0;
                Teams[j].goalsByTeam = 0;
                Teams[j].goalsOnTeam = 0;
            }

            if (strcmp(Teams[j].teamName, Games[i].team1Name) == 0 || strcmp(Teams[j].teamName, Games[i].team2Name) == 0) {
                /* Team 1 */
                if (strcmp(Teams[j].teamName, Games[i].team1Name) == 0) {
                    Teams[j].goalsByTeam += Games[i].team1Score;
                    Teams[j].goalsOnTeam += Games[i].team2Score;

                    if (Games[i].team1Score > Games[i].team2Score)
                        Teams[j].points += WON_POINTS;
                    
                    if (Games[i].team1Score == Games[i].team2Score)
                        Teams[j].points += DRAW_POINTS;
                }

                /* Team 2 */
                if (strcmp(Teams[j].teamName, Games[i].team2Name) == 0) {
                    Teams[j].goalsByTeam += Games[i].team2Score;
                    Teams[j].goalsOnTeam += Games[i].team1Score;

                    if (Games[i].team1Score < Games[i].team2Score)
                        Teams[j].points += WON_POINTS;
                    
                    if (Games[i].team1Score == Games[i].team2Score)
                        Teams[j].points += DRAW_POINTS;
                }
            }
        }
    }

    /* printf("---- Unsorted ----\n");
    printf(" Team | Score | Goals | Goal on team\n");
    for (i = 0; i < count; i++)
    {
        printf("%5s | %5d | %5d | %5d\n", Teams[i].teamName, Teams[i].points, Teams[i].goalsByTeam, Teams[i].goalsOnTeam);
    }

    printf("\n");

    qsort(Teams, count, sizeof(team), compareMatch);
    
    printf("---- Sorted ----\n");
    printf(" Team | Score | Goals | Goal on team\n");
    for (i = 0; i < count; i++)
    {
        printf("%5s | %5d | %5d | %5d\n", Teams[i].teamName, Teams[i].points, Teams[i].goalsByTeam, Teams[i].goalsOnTeam);
    } */

    printf("test\n");

    for (i = 0; i < count; i++)
    {
        hashNum = hash(((unsigned char *)Teams[i].teamName));

        printf("Hash of team %s is %d\n", Teams[i].teamName, hashNum);

        /* TeamsHash[hashNum]->teamName = Teams[i].teamName; */#
        TeamsHash[hashNum].teamName = Teams[i].teamName;
    }

    /* AaB, VB, ACH and FCK overlap on 9 */
    
    fclose(fp); 
        
    return EXIT_SUCCESS;
}

int compareMatch(const void *a, const void *b) {
    team *A = (team *)a;
    team *B = (team *)b;

    if (A->points != B->points)
        return B->points - A->points;

    return (B->goalsByTeam - B->goalsOnTeam) - (A->goalsByTeam - A->goalsOnTeam);
}

/* djb2 hashing funciton */
int hash(unsigned char *str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    /* TODO currently assumes array size is 12 */
    return hash % 12;
}