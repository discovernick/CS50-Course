#include <stdio.h>
#include <cs50.h>

bool valid_triangle(float a, float b, float c);

int main(void) {
    float triangle[3];
    for (int i = 0; i < 3 ; i++ ) {
        scanf("%f", &triangle[i]);
    }
    if (valid_triangle(triangle[0], triangle[1], triangle[2]) != 0) {
        printf("Error!\n");
    }
}

bool valid_triangle(float a, float b, float c) {
    // Check all sides are positive
    if ( a <= 0 || b <= 0 || c <= 0 ) {
        return 1;
    }
    // Check sum
    if ( a + b <= c  || a + c <= b || b + c <= a ) {
        return 1;
    }
    return 0;
}