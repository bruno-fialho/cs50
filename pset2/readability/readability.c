// index = 0.0588 * L - 0.296 * S - 15.8
// L = average number of letters per 100 words in the text
// S = average number of sentences per 100 words in the text

#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

// Declare global variables
float L;
float S;

int main(void)
{

    // Prompt for a text
    string text = get_string("Text: ");


    // Declare variables
    int letters = 0;
    int words = 1;
    int sentences = 0;
    char character;
    int index;

    int len = strlen(text);

    // Loop through the text
    for (int i = 0; i < len; i++)
    {
        // Get the character at position 'i'
        character = text[i];

        // Check if is alpha and add to letters
        if (isalpha(character))
        {
            letters++;
        }

        // Check if is space and add to words
        else if (character == ' ')
        {
            words++;
        }

        // Check if is '.', '!' or '?' and add to sentences
        else if (character == '.' || character == '!' || character == '?')
        {
            sentences++;
        }
    }

    // L = average number of letters per 100 words in the text
    L = (float)(letters * 100) / words;


    // S = average number of sentences per 100 words in the text
    S = (float)(sentences * 100) / words;


    // Calculate Coleman-Liau Index
    index = round(0.0588 * L - 0.296 * S - 15.8);


    // Print the grade level of the text
    if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}