from cs50 import get_int

# Prompt the uesr for height until a valid number: 1-8
n = 0

while n < 1 or n > 8:
    n = get_int("Height: ")

# For loop to print each line
for i in range(n):
    # Print spaces
    for a in range(n - i - 1):
        print(" ", end="")

    # Print left hashes
    for b in range(i + 1):
        print("#", end="")

    # Print gap
    print("  ", end="")

    # Print right hashes
    for c in range(i + 1):
        print("#", end="")

    # Break line
    print()
