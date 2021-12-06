/* Name: Lucas Mørk Frendorf */
/* Group: B201 */
/* Ran using: gcc filename.c -ansi -Wall -pedantic && ./a.out && rm a.out */
/* Ran on: Linux [x86_64] */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Symbolic constants */
#define WON_POINTS 3
#define DRAW_POINTS 1

#define TEAMS 12 

typedef struct
{
    char teamName[4];
    int points;
    int goalsByTeam;
    int goalsOnTeam;
} team;

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
int teamNumber(char name[]);
int compareMatch(const void *a, const void *b);

int main(void) {
    game *Games;
    team Teams[TEAMS] = {0};
    int i, lines = 0;
    int ch;

    FILE *fp;

    if ((fp = fopen("kampe-2020-2021.txt","r")) == NULL){
        printf("Error! opening file");
        return EXIT_FAILURE;
    }

    /* TODO maybe use fseek and double line jump each time */
    /* Get the amount of games in our files */
    while(!feof(fp))
    {
        ch = fgetc(fp);

        if(ch == '\n')
        {
            lines++;
        }
    }

    Games = (game *) malloc(sizeof(game) * lines);

    /* Go back to the first line again */
    fseek(fp, 0, SEEK_SET );

    for (i = 0; i < lines; i++)
    {
        fscanf(fp, "%s     %s %s     %s - %s     %i - %i     %i", Games[i].day, Games[i].date, Games[i].clock, Games[i].team1Name, Games[i].team2Name, &Games[i].team1Score, &Games[i].team2Score, &Games[i].spectators);

        strcpy(Teams[teamNumber(Games[i].team1Name)].teamName, Games[i].team1Name);
        strcpy(Teams[teamNumber(Games[i].team2Name)].teamName, Games[i].team2Name);

        Teams[teamNumber(Games[i].team1Name)].goalsByTeam += Games[i].team1Score;
        Teams[teamNumber(Games[i].team1Name)].goalsOnTeam += Games[i].team2Score;

        Teams[teamNumber(Games[i].team2Name)].goalsByTeam += Games[i].team2Score;
        Teams[teamNumber(Games[i].team2Name)].goalsOnTeam += Games[i].team1Score;

        if (Games[i].team1Score == Games[i].team2Score) { /* Equal score */
            Teams[teamNumber(Games[i].team1Name)].points += DRAW_POINTS;
            Teams[teamNumber(Games[i].team2Name)].points += DRAW_POINTS;
        } else if (Games[i].team1Score > Games[i].team2Score) { /* Team 1 won */
            Teams[teamNumber(Games[i].team1Name)].points += WON_POINTS;
        } else if (Games[i].team1Score < Games[i].team2Score) { /* Team 2 won */
            Teams[teamNumber(Games[i].team2Name)].points += WON_POINTS;
        }
    }

    printf("---- Unsorted ----\n");
    printf(" Team | Score | Goals | Goal on team\n");
    for (i = 0; i < TEAMS; i++)
    {
        printf("%5s | %5d | %5d | %5d\n", Teams[i].teamName, Teams[i].points, Teams[i].goalsByTeam, Teams[i].goalsOnTeam);
    }

    printf("\n");

    qsort(Teams, TEAMS, sizeof(team), compareMatch);
    
    printf("---- Sorted ----\n");
    printf(" Team | Score | Goals | Goal on team\n");
    for (i = 0; i < TEAMS; i++)
    {
        printf("%5s | %5d | %5d | %5d\n", Teams[i].teamName, Teams[i].points, Teams[i].goalsByTeam, Teams[i].goalsOnTeam);
    }

    fclose(fp); 
        
    return EXIT_SUCCESS;
}

int teamNumber(char name[]) {
    if (strcmp(name ,"SDR") == 0) {
        return 0;
    } else if (strcmp(name ,"FCM") == 0) {
        return 1;
    } else if (strcmp(name ,"ACH") == 0) {
        return 2;
    } else if (strcmp(name ,"RFC") == 0) {
        return 3;
    } else if (strcmp(name ,"LBK") == 0) {
        return 4;
    } else if (strcmp(name ,"AaB") == 0) {
        return 5;
    } else if (strcmp(name ,"BIF") == 0) {
        return 6;
    } else if (strcmp(name ,"FCN") == 0) {
        return 7;
    } else if (strcmp(name ,"OB") == 0) {
        return 8;        
    } else if (strcmp(name ,"FCK") == 0) {
        return 9;
    } else if (strcmp(name ,"AGF") == 0) {
        return 10;
    } else if (strcmp(name ,"VB") == 0) {
        return 11;
    }

    printf("Hey something went wrong!\n");
    return EXIT_FAILURE;
}

int compareMatch(const void *a, const void *b) {
    team *A = (team *)a;
    team *B = (team *)b;

    if (A->points != B->points)
        return B->points - A->points;

    return (B->goalsByTeam - B->goalsOnTeam) - (A->goalsByTeam - A->goalsOnTeam);
}