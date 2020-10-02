#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
    long number;
    int length;

    // Prompt for a card number
    do
    {
        number = get_long("Number: ");
    }
    while (number < 1);


    // Get length
    length = floor(log10(labs(number))) + 1;

    // Check if length is valid
    if (length < 13 || length > 16 || length == 14)
    {
        printf("INVALID\n");
        return 0;
    }

    // Declare the variables
    int result = 0;
    int digit;
    int second_digit = 0;
    int count = 0;

    // Loop through the number to calculate checksum and get first two digits
    while (number)
    {
        second_digit = digit;

        digit = number % 10;

        number /= 10;

        // If num
        if (count % 2 == 0)
        {
            result += digit;
        }
        else
        {
            if (digit < 5)
            {
                result += 2 * digit;
            }
            else
            {
                result += ((2 * digit) % 10) + 1;
            }
        }

        count++;
    }

    // Check if the number is valid
    if (result % 10 == 0)
    {

        // For length = 13 - Check if it is VISA
        if (length == 13)
        {
            if (digit == 4)
            {
                printf("VISA\n");
                return 0;
            }

            else
            {
                printf("INVALID\n");
                return 0;
            }
        }

        // For length = 15 - Check if it is AMEX
        else if (length == 15)
        {
            if (digit == 3)
            {
                if (second_digit == 4 || second_digit == 7)
                {
                    printf("AMEX\n");
                    return 0;
                }

                else
                {
                    printf("INVALID\n");
                    return 0;
                }
            }

            else
            {
                printf("INVALID\n");
                return 0;
            }
        }

        // For length = 15 - Check if it is VISA or MASTERCARD
        else if (length == 16)
        {
            if (digit == 4)
            {
                printf("VISA\n");
                return 0;
            }

            else if (digit == 5)
            {
                if (second_digit > 0 && second_digit < 6)
                {
                    printf("MASTERCARD\n");
                    return 0;
                }

                else
                {
                    printf("INVALID\n");
                    return 0;
                }
            }

            else
            {
                printf("INVALID\n");
                return 0;
            }
        }

        // If number is valid but do not fit any condition
        else
        {
            printf("INVALID\n");
            return 0;
        }
    }

    // If number is not valid
    else
    {
        printf("INVALID\n");
        return 0;
    }
}
