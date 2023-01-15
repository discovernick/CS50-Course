// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Implement global storage of size
unsigned int *sizeptr = NULL;

// TODO: Choose number of buckets in hash table
const unsigned int N = 54;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Hash word to obtain hash value
    unsigned int index = hash(word);
    // Access the linked list in the hash table
    node *currentptr = table[index];
    // Traverse linked list

    while (currentptr != NULL)
    {
        if (strcasecmp(currentptr->word, word) == 0)
        {
            return true;
        }
        currentptr = currentptr->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int index = 0;

    // Split world length
    if (strlen(word) > 8)
    {
        index = index + 26;
    }
    // Split by first letter
    index = index + ((int)tolower(word[0]) - 97);
    // Split by second letter
    // index = index + ((int)word[1]-97);
    return index;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Create size pointer
    sizeptr = malloc(sizeof(unsigned int));

    // Establish counter variable
    int counter = 0;

    // Open dictionary file and check if opened succesfully
    FILE *inptr = fopen(dictionary, "r");
    if (inptr == NULL)
    {
        printf("File not succesfully loaded");
        return false;
    }

    // Read Strings from file one at a time
    char current_word[LENGTH + 1];
    int index = 0;
    while (fscanf(inptr, "%s", current_word) != EOF)
    {

        // Create a new node for each word
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("Malloc not succesfully loaded");
            return false;
        }
        /* Copy over the value into the given node */
        strcpy(n->word, current_word);
        index = hash(current_word);

        /* First Step: Assign the new node to point to the first element in the linked list */
        if (table[index] == NULL)
        {
            table[index] = n;
            n->next = NULL;
        }
        else
        {
            n->next = table[index];
            table[index] = n;
        }
        counter++;
    }
    *sizeptr = counter;
    fclose(inptr);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    unsigned int index = *sizeptr;
    free(sizeptr);
    return index;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    /* Establish temporary pointer and current pointer */
    node *tmp = NULL;
    node *currentptr = NULL;

    for (int i = 0; i < N; i++)
    {
        currentptr = table[i];
        // tmp = currentptr->next;
        while (currentptr != NULL)
        {
            tmp = currentptr;
            currentptr = currentptr->next;
            free(tmp);
            // tmp = currentptr->next;
        }
    }

    return true;
}


