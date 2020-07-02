from cs50 import SQL
from sys import argv, exit
import csv

# Create empty students.db
open("students.db", "w").close()

# Open SQL Database for sqlite to save student info
db = SQL("sqlite:///students.db")

# Create table students in database students.db
db.execute("CREATE TABLE students(First TEXT, Middle TEXT, Last TEXT, House TEXT, Birth NUMERIC)")

# Check for command line arguments
if len(argv) != 2:
    print("Usage: python import.py file.csv")
    exit(1)

# If CSV file exists
else:

    # Open file
    csv_names = argv[1]
    with open(csv_names, "r") as names:
        reader = csv.reader(names)

        #Skip first row
        next(reader)

        # Dictionary to store student info
        dict_houses = {"First:":"", "Middle":"", "Last:":"", "House":"", "Birth":""}

        for row in reader:

            # Names
            if row[0]:

                # Splits string into list of names
                s = row[0].split()

                # Joins the item in list to a string
                first = ''.join(s[0:1])
                last = ''.join(s[-1])

                if len(s) > 2:

                    middle = ''.join(s[1:-1])

                else:

                    middle = "NULL"

                # Add to dictionary
                dict_houses.update({"First:": first, "Middle": middle, "Last:": last})

            # Houses
            if row[1]:

                house = "".join(row[1])
                dict_houses["House"] = house
                db.execute("INSERT INTO students(House) VALUES(?)",
                house)

            # Birth year
            if row[2]:

                birth = "".join(row[2])
                dict_houses["Birth"] = birth
                db.execute("INSERT INTO students(Birth) VALUES(?)",
                birth)
            print(dict_houses.values())

    # Write to database
    
    #db.execute("INSERT INTO students(First, Middle, Last) VALUES(?,?,?)",
    #            first, middle, last)