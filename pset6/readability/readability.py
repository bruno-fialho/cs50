# index = 0.0588 * L - 0.296 * S - 15.8
# L = average number of letters per 100 words in the text
# S = average number of sentences per 100 words in the text
from cs50 import get_string

# Prompt for a text
while True:
    text = get_string("Text: ")
    if text != '':
        break

# Declare variables
letters = 0
words = 1
sentences = 0
index = 0

length = len(text)

# Loop through the text
for i in range(length):

    # Get the character at position 'i'
    character = text[i]

    # Check if is alpha and add to letters
    if character.isalpha():
        letters += 1

    # Check if is space and add to words
    elif character == ' ':
        words += 1

    # Check if is '.', '!' or '?' and add to sentences
    elif character == '.' or character == '!' or character == '?':
        sentences += 1

# L = average number of letters per 100 words in the text
L = float((letters * 100) / words)

# S = average number of sentences per 100 words in the text
S = float((sentences * 100) / words)

# Calculate Coleman-Liau Index
index = round(0.0588 * L - 0.296 * S - 15.8)

# Print the grade level of the text
if index > 16:
    print("Grade 16+")

elif (index < 1):
    print("Before Grade 1")

else:
    print("Grade " + str(index))
