from sys import argv, exit
import csv

# Check number of command-line arguments
if len(argv) != 3:
    print("Usage: python dna.py data.csv sequence.txt")
    exit(1)

# Declare an empty array for data
people = []
fields = []

# Read CSV file and store data to people
with open(argv[1], mode='r') as data:
    reader = csv.DictReader(data)

    for field in reader.fieldnames:
        fields.append(field)

    for row in reader:
        row = dict(row)
        person = row

        people.append(person)

STRs = fields[1:]

# Read DNA sequence and store data to a list
with open(argv[2], mode='r') as f:
    sequence = f.read().rstrip()


# Get sequence length
length = len(sequence)

# Create a dictionary list for STRs count
sequence_count = {}

for STR in STRs:
    sequence_count[STR] = 0


# Compute the longest run for each str
for STR in STRs:
    # Init count to 0
    count = 0

    # Get STR length
    str_len = len(STR)

    # Get first valid index from the end
    index = length - str_len

    # Loop from end to start of sequence
    while index >= 0:

        # If STR is found
        if (sequence[index:index + str_len] == STR):
            count += 1

            index -= str_len

            # If next index < 0, stop!
            if index < 0:

                # Check if count is higher than previous
                if count > sequence_count[STR]:
                    sequence_count[STR] = count

        # If STR is not found
        else:
            index -= 1

            # If count was > 0 or next index < 0
            if count > 0 or index < 0:

                # Check if count is higher than previous
                if count > sequence_count[STR]:
                    sequence_count[STR] = count

            # Restart count
            count = 0

found = []

# Check if STR counts matches a person
for person in people:
    match = 0

    # For each of STRs
    for STR in STRs:

        # Compare csv value with sequence
        if int(person[STR]) == sequence_count[STR]:
            match += 1

    # Append match name to found
    if match == len(STRs):
        found.append(person['name'])

if len(found) == 1:
    print(found[0])

else:
    print("No match")
