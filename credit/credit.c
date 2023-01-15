#include <cs50.h>
#include <stdio.h>
#include <math.h> //added for log base 10 calcs
#include <stdlib.h>

int main(void)
{
    unsigned long long int number = 0;
    int nDigits = 0;
    int y = 0;
    int i = 0;
    int x1 = 0;
    int x2 = 0;


    // Get input from user
    // AMEX = 15 digit & Starts with 34 or 37
    // Mastercard = 16 digit numbers with 51, 52, 53, 54, or 55
    // VISA = 13 or 16 digit numbers & Start with a 4

    while (y == 0) {
        printf("Number:  ");
        scanf("%llu", &number);
        nDigits = floor(log10(number)) + 1;
        // printf("\n%d", nDigits);
        if (nDigits == 13 || nDigits == 15 ||nDigits == 16) {
            y++;
        } else {
            printf("INVALID\n");
            exit(0);
        }
    }

    // char str[nDigits];

    char multiplied[8];
    char added[8];
    unsigned long long int holder = 0;
    int current_digit = 0;
    holder = number;

    // Convert to string
    while (i < nDigits) {
        current_digit = holder % 10;
        holder /= 10;
        // printf("%d", current_digit);
        if (i % 2 == 0) {
            added[x2] = current_digit;
            x2++;
        } else {
            multiplied[x1] = current_digit;
            x1++;
        }
        i++;
    }

    // Work through the string - multiplication first
    i = 0;
    int multiplied_sum = 0;
    while (i < 8) {
        current_digit = 2*multiplied[i];
        if (current_digit < 10) {
            multiplied_sum = multiplied_sum + current_digit;
        } else {
            multiplied_sum = multiplied_sum + (current_digit % 10);
            multiplied_sum = multiplied_sum  + (current_digit /= 10);
        }
        i++;
    }

    // Woth through the string - pure addition
    i = 0;
    int added_sum = 0;
    while (i < 8) {
        current_digit = added[i];
        added_sum = added_sum + current_digit;
        i++;
    }

    //int AMEX = number /= 10000000000000;
    //printf("%llu\n",number);
    //printf("%d\n",AMEX);

    // Check condition of addition
    int final_sum = added_sum + multiplied_sum;
    if (final_sum % 10 != 0) {
        printf("INVALID\n");
    } else if (nDigits == 15) {
        if ((number / 10000000000000) == 34 || (number / 10000000000000) == 37) {
            printf("AMEX\n");
        } else {
            printf("INVALID\n");
        }
    } else if (nDigits == 13) {
        // printf("%llu\n",number);
        if ((number / 1000000000000) == 4) {
            printf("VISA\n");
        } else {
            printf("INVALID\n");
        }
    } else {
        if ((number / 1000000000000000) == 4) {
            printf("VISA\n");
        } else if ((number / 100000000000000) == 51 || (number / 100000000000000) == 52 || (number / 100000000000000) == 53 || (number / 100000000000000) == 54 || (number / 100000000000000) == 55) {
            printf("MASTERCARD\n");
        } else {
            // printf("%llu\n",number / 100000000000000);
            // printf("%llu\n",number);
            printf("INVALID\n");
        }
    }



}