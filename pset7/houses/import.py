from sys import argv, exit
import cs50
import csv

# Check number of command-line arguments
if len(argv) != 2:
    print("Usage: python import.py file.csv")
    exit(1)

# Set up a database connection
db = cs50.SQL("sqlite:///students.db")

# Open csv file
with open(argv[1], "r") as file:
    reader = csv.DictReader(file)

    # Loop all rows (students) in file
    for row in reader:

        # Split name from csv
        words = row['name'].split()

        # Check if student has middle name
        if len(row['name'].split()) == 3:

            # Save name with middle name
            first = words[0]
            middle = words[1]
            last = words[2]

        else:

            # Save name without middle name
            first = words[0]
            middle = None
            last = words[1]

        # Save house and birth  variables
        house = row['house']
        birth = row['birth']

        # Insert students
        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)", first, middle, last, house, birth)

