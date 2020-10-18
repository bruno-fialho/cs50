from sys import exit
from cs50 import get_int

# Prompt for a card number
while True:
    number = get_int("Number: ")
    if number > 0:
        break

# Get length
length = len(str(number))

# Get first adn second digit
first_digit = int(str(number)[0])
second_digit = int(str(number)[1])


# Define a function for checksum
def checksum(number):
    # Declare the variables
    result = 0
    count = 0
    tmp = number
    length = len(str(number))

    # Loop through the number to calculate checksum
    while count < length:
        digit = int(tmp % 10)

        tmp = int(tmp / 10)

        # If number is in the second-to-last group
        if count % 2 == 0:
            result += digit

        else:
            # If product is less than 10 (1 digit)
            if digit < 5:
                result += 2 * digit

            # If product is higher than 9 (2 digits)
            else:
                result += ((2 * digit) % 10) + 1

        count += 1

    return result % 10 == 0


# For length = 13 - Check if it is VISA
if length == 13 and first_digit == 4 and checksum(number):
    print("VISA")
    exit(0)

# For length = 15 - Check if it is AMEX
elif length == 15 and first_digit == 3 and (second_digit == 4 or second_digit == 7) and checksum(number):
    print("AMEX")
    exit(0)

# For length = 16 - Check if it is VISA
elif length == 16 and first_digit == 4 and checksum(number):
    print("VISA")
    exit(0)

# For length = 16 - Check if it is MASTERCARD
elif length == 16 and first_digit == 5 and second_digit > 0 and second_digit < 6 and checksum(number):
    print("MASTERCARD")
    exit(0)

# If number is not valid
else:
    print("INVALID")
    exit(1)
