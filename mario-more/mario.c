#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int number = 0;
    int y = 1;
    int i = 0;

    // Get input from user

    while (number == 0) {
        printf("Height:  ");
        scanf("%d", &number);
        if (number <= 0 || number > 8) {
            number = 0;
        }
    }

    // Print output
    while (y <= number) {
        // 1. Print Spaces
        for (i = 0; i < number - y; i++) {
            printf(" ");
        }
        // 2. Print Blocks
        for (i = 0; i < y; i++) {
            printf("#");
        }
        // 3. Print Central Spaces
        printf("  ");
        // 4. Print Blocks
        for (i = 0; i < y; i++) {
            printf("#");
        }
        // 5. Print Spaces
        // printf(" ");
        // Down a level
        printf("\n");
        y++;
    }
}