// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 143093;

// Hash table
node *table[N];

// Represents size of dictionary
int dict_size = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Pointer to first node of bucket
    unsigned int h = hash(word);

    node *cursor = table[h];

    // Check all dictionary
    while (cursor != NULL)
    {
        // Create temporary cursor
        node *tmp = cursor;

        // Set cursor to next
        cursor = cursor->next;

        // Create a temporary lowercase word
        int len = strlen(word) + 1;

        char lowercase_word[len];

        for (int i = 0, j = len; i < j; i++)
        {
            lowercase_word[i] = tolower(word[i]);
        }

        // Compare *word with dictionary node word
        if (strcmp(lowercase_word, tmp->word) == 0)
        {
            return true;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Polynomial hash function - Horner’s rule
    // https://www.cs.umd.edu/class/fall2019/cmsc420-0201/Lects/lect10-hash-basics.pdf

    // Get word length
    int len = strlen(word);

    // Define a prime number
    int a = 33;

    // Define index
    int index = 0;

    // Horner`s Rule
    for (int i = len - 1; i >= 0; i--)
    {
        index = a * index + tolower(word[i]);
    }

    // Compression (N is a prime number)
    index = index % N;

    return index;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Open dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // Read strings from file
    while (fscanf(file, "%s", word) != EOF)
    {
        // Create a new node for each word
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            return false;
        }

        strcpy(new_node->word, word);

        // Hash word to obtain a hash value
        int new_hash = hash(word);

        // Insert node into hash table at that location
        if (table[new_hash] == NULL)
        {
            new_node->next = NULL;
            table[new_hash] = new_node;
        }
        else
        {
            new_node->next = table[new_hash];
            table[new_hash] = new_node;
        }

        dict_size++;
    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return dict_size;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // For loop over buckets
    for (int i = 0; i < N; i++)
    {
        // Point cursor to first node
        node *cursor = table[i];

        // Loop over nodes
        while (cursor != NULL)
        {
            // Move a tmp cursor to next node
            node *tmp = cursor->next;

            // Free cursor
            free(cursor);

            // Makes cursor equal to tmp
            cursor = tmp;
        }
    }
    return true;
}
