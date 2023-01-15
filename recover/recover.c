#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define SIZE 512

int main(int argc, char *argv[])
{
    // Prevent invalid input into the system
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE");
        return 1;
    }

    // Open main file to read and check it loads
    FILE *inptr = fopen(argv[1], "r");
    if (inptr == NULL)
    {
        printf("Could not open.\n");
        return 2;
    }

    // Declare Variables
    int new = 0;
    int opened = 0;
    int file_counter = -1;
    char name[] = "000.jpg";
    char jpg[] = ".jpg";
    typedef uint8_t BYTE;
    BYTE *arr = malloc(SIZE * sizeof(BYTE));
    int first = 0xff;
    int second = 0xd8;
    int third = 0xff;
    int fourth[] = {0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, 0xef};
    char *file_name;

    FILE *outptr = (FILE *) NULL;

    while ((fread(arr, 1, SIZE, inptr)) == SIZE)
    {
        // Check for Condition 1
        if (arr[0] == first)
        {
            // Check for Condition 2
            if (arr[1] == second)
            {
                // Check for Condition 3
                if (arr[2] == third)
                {
                    // Check for Codition 4
                    for (int j = 0; j < 16; j++)
                    {
                        if (arr[3] == fourth[j])
                        {
                            new++;
                            break;
                        }
                    }

                    if (new == 1)
                    {
                        // File Naming
                        file_counter++;
                        if (file_counter < 10)
                        {
                            name[0] = '0';
                            name[1] = '0';
                            sprintf(&name[2], "%d", file_counter);
                            sprintf(&name[3], "%s", jpg);
                        }
                        else if (file_counter < 100)
                        {
                            name[0] = '0';
                            sprintf(&name[1], "%d", file_counter / 10);
                            sprintf(&name[2], "%d", file_counter % 10);
                            sprintf(&name[3], "%s", jpg);
                            // name[1] = file_counter / 10;
                            // name[2] = file_counter % 10;
                        }
                        else
                        {
                            sprintf(&name[0], "%d", file_counter / 100);
                            sprintf(&name[2], "%d", file_counter % 10);
                            sprintf(&name[2], "%d", file_counter % 10);
                            sprintf(&name[3], "%s", jpg);
                            // name[0] = file_counter / 100;
                            // name[1] = file_counter / 10;
                            // name[2] = file_counter % 10;
                        }
                        file_name = name;

                        // Closing Old and Opening New File
                        if (file_counter != 0)
                        {
                            fclose(outptr);
                        }
                        outptr = fopen(file_name, "w");
                        if (outptr == NULL)
                        {
                            printf("broken\n");
                            return 1;
                        }
                        fwrite(arr, SIZE, 1, outptr);
                        new = 0;
                    }
                    else if (file_counter >= 0)
                    {
                        fwrite(arr, SIZE, 1, outptr);
                    }
                }
                else if (file_counter >= 0)
                {
                    fwrite(arr, SIZE, 1, outptr);
                }
            }
            else if (file_counter >= 0)
            {
                fwrite(arr, SIZE, 1, outptr);
            }
        }
        else if (file_counter >= 0)
        {
            fwrite(arr, SIZE, 1, outptr);
        }
    }
    fclose(outptr);
    free(arr);
    fclose(inptr);
    return 0;
}