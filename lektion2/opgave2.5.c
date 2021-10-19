#include <stdio.h>

int main(void) {
    // Using unsigned since we only wanna use positive numbers
    unsigned int input;

    printf(" Amount of second(s) you wanna convert (0 - 4294967295): ");
    scanf("%u", &input);

    // Converts input into the correct time format and then use modulo to get the remainder
    unsigned int seconds = input % 60;
    unsigned int minutes = input / 60 % 60;
    unsigned int hours = input / (60 * 60) % 24;
    unsigned int days = input / (60 * 60 * 24) % 7;
    unsigned int weeks = input / (60 * 60 * 24 * 7);

    printf(" %d week(s), %d day(s), %d hour(s), %d minute(s), %d second(s)", weeks, days, hours, minutes, seconds);

    return 0;
}