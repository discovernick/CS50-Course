#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

// Call function prototypes
float count_letters(string word);
float count_words(string word);
float count_sentences(string word);

int main(void)
{
    // Initialise variables
    float L = 0.00;
    float S = 0.00;
    float index = 0.00;

    // Lets get user input
    string matter = get_string("Text: ");
    // printf("%s", matter);

    // Counting letters
    L = (count_letters(matter) / count_words(matter)) * 100;
    S = (count_sentences(matter) / count_words(matter)) * 100;
    index = 0.0588 * L - 0.296 * S - 15.8;


    // Print Output
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        index = round(index);
        // index = (int)index;
        printf("Grade %d\n", (int)index);
    }
}

float count_letters(string word)
{
    // Initialise points counter
    int counter = 0;
    for (int i = 0; i < strlen(word) ; i++)
    {
        // Remove capitals first
        word[i] = tolower(word[i]);

        // Counting the actual letters
        if (word[i] >= 97 && word[i] <= 122)
        {
            counter++;
        }
    }
    // printf("Letters: %d\n", counter);
    return counter;
}

float count_words(string word)
{
    // Initialise points counter
    int counter = 0;
    for (int i = 0; i < strlen(word) ; i++)
    {
        // Counting the spaces
        if (word[i] == 32)
        {
            counter++;
        }
    }
    counter++;
    // printf("Words: %d\n", counter);
    return counter;
}

float count_sentences(string word)
{
    // Initialise points counter
    int counter = 0;

    for (int i = 0; i < strlen(word) ; i++)
    {

        // Counting the . ? !
        if (word[i] == 46 || word[i] == 33 || word[i] == 63)
        {
            counter++;
        }
    }
    // printf("Sentences: %d\n", counter);
    return counter;
}