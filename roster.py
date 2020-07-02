from cs50 import SQL
from sys import argv, exit


# Define function that prints all names from a given house
def print_house(table):
    for i in table:
        
        print(i["first"], end = ' ')
        
        if i["middle"] != "NULL":
            continue

        print(i["last"], end = ', ')
        print("born", i["birth"])
    return


def main():
    # Check for command line argument (house)
    if len(argv) != 2:
        print("Usage: python roster.py Gryffindor")
        exit(1)

    # Open SQL Database to run queries
    db = SQL("sqlite:///students.db")

    # Query the students table in the students.db database for all of the students in the specified house.
    house = argv[1]
    rows = db.execute("SELECT * FROM students WHERE house = ? ORDER BY last ASC, first ASC", house)

    # Print names of everyone in given house
    print_house(rows)

if __name__ == '__main__':
    main()