#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n;

    // Prompt the uesr for height until a valid number: 1-8
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);

    // For loop to print each line
    for (int i = 0; i < n; i++)
    {
        // Print spaces
        for (int a = 0; a < n - i - 1; a++)
        {
            printf(" ");
        }

        // Print left hashes
        for (int b = 0; b < i + 1; b++)
        {
            printf("#");
        }

        // Print gap
        printf("  ");

        // Print right hashes
        for (int c = 0; c < i + 1; c++)
        {
            printf("#");
        }

        // Break line
        printf("\n");
    }
}
