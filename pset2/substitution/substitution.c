#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // Check if there is at least and only one argument
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // Check if key has 26 characters
    else if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    for (int i = 0; i < 26; i++)
    {
        // Check if all key characters are alphabetic
        if (!isalpha(argv[1][i]))
        {
            printf("Key must only contain alphabetic characters.\n");
            return 1;
        }

        // Check if key do not contain repeated characters
        else
        {
            for (int j = 0; j < i; j++)
            {
                if (argv[1][i] == argv[1][j])
                {
                    printf("Key must not contain repeated characters.\n");
                    return 1;
                }
            }
        }
    }

    string key = argv[1];

    // Prompt user for text
    string text = get_string("plaintext: ");

    // Declare variables
    int length = strlen(text);
    int position;
    char ciphertext[length];

    // Print first part of output
    printf("ciphertext: ");

    // Loop through text
    for (int i = 0; i < length; i++)
    {
        // If letter is uppercase
        if (isupper(text[i]))
        {
            position = (int)text[i] - 65;

            printf("%c", toupper(key[position]));
        }

        // If letter is lowercase
        else if (islower(text[i]))
        {
            position = (int)text[i] - 97;

            printf("%c", tolower(key[position]));
        }

        // If character is not a letter
        else
        {
            printf("%c", text[i]);
        }
    }

    // Print new line and return 0
    printf("\n");
    return 0;


}
