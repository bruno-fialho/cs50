from sys import argv, exit
import cs50
import csv

# Check number of command-line arguments
if len(argv) != 2:
    print("Usage: python roster.py House")
    exit(1)

# Set up a database connection
db = cs50.SQL("sqlite:///students.db")

# Get house name
house = argv[1]

# Select all students from the house
students = db.execute("SELECT first, middle, last, birth FROM students WHERE house = ? ORDER BY last, first ASC", house)

# Loop all rows to print students
for student in students:

    # Get variables
    first = student['first']
    middle = student['middle']
    last = student['last']
    birth = student['birth']

    # Check if student has middle name
    if student['middle'] != None:

        # Print student with middlename
        print(first + " " + middle + " " + last + ", born " + str(birth))

    else:

        # Print student without middle name
        print(first + " " + last + ", born " + str(birth))
