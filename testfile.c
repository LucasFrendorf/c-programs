#include <stdio.h>

int main(void) {
    int i = 0, j = 1, k = 2;

    i++;
    j + i;
    k = j++;

    printf("%d", k);

    return 0;
}