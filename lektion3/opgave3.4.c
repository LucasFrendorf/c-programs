#include <stdio.h>
#include <stdlib.h>

#define SEC_IN_MINUTE 60
#define SEC_IN_HOUR (60 * SEC_IN_MINUTE)
#define SEC_IN_DAY (24 * SEC_IN_HOUR)

int main() {
    // Using unsigned since we only wanna use positive numbers
    unsigned int input;

    printf(" Amount of second(s) you wanna convert (1 - 4294967295): ");
    scanf("%u", &input);

    if (input == 0) {
        printf(" Please input a number larger than 1");
        return EXIT_FAILURE;
    }

    // Converts input into the correct time format and then use modulo to get the remainder
    unsigned int seconds = input % (SEC_IN_MINUTE);
    unsigned int minutes = input / SEC_IN_MINUTE % SEC_IN_MINUTE;
    unsigned int hours = input / SEC_IN_HOUR % SEC_IN_HOUR;

    int hasValue[3] = {hours > 0, minutes > 0, seconds > 0};
    char names[][7] = {"hour", "minute", "second"};
    unsigned int values[] = {hours, minutes, seconds};

    input > 1 ? printf(" %u seconds corresponds to ", input) : printf(" %u second corresponds to ", input);

    int i;
    for (i = 0; i < 3; ++i) {
        if (hasValue[i]) {
            values[i] == 1 ?  printf("%u %s", values[i], names[i]) : printf("%u %ss", values[i], names[i]);

            // Check the next value(s) and print "and" or "," depending on the values
            if (hasValue[i+1] == 1 && hasValue[i+2] == 1) {
                printf(", ");
            } else if (hasValue[i+1] == 0 && hasValue[i+2] == 1 || hasValue[i+1] == 1 && i != 2) {
                printf(" and ");
            }
        }
    }

    printf(".\n");

    return EXIT_SUCCESS;
}