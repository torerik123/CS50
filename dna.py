from sys import argv, exit
import csv


def get_max(dnastring, STR):

    # Iteration values. [0:5] if the word has 5 letters.
    i = 0
    j = len(STR)

    # Count repetitions
    maxval = 0

    for x in range(len(dnastring)):
        if dnastring[i:j] == STR:
            temp = 0

            # When a match is found start to count the consecutive matches until there's no match.
            while dnastring[i:j] == STR:
                temp += 1

                # Increment by len of i and j to search for another match
                i += len(STR)
                j += len(STR)

                if temp > maxval:
                    maxval = temp

        # If no match, increment by 1 to check next substring
        else:
            i += 1
            j += 1

    return maxval


def print_match(reader, actual):
    for line in reader:
        # Name
        person = line[0]

        # Convert strings in database to ints and store in array
        values = [int(val) for val in line[1:]]

        # Compares every element in the values array to actual array and prints the name if all values match
        if values == actual:
            print(person)
            return
    print("No match")


def main():

    # Check for command line arguments
    if len(argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        exit(1)

    # Open DNA database from command line argument
    csv_database = argv[1]
    with open(csv_database) as csv_file:
        reader = csv.reader(csv_file)

        # Stores values of all sequences, skipping the names
        DNAsequences = next(reader)[1:]

        # Open DNA string from command line argument
        DNA_string = argv[2]
        with open(DNA_string) as txt_file:
            s = txt_file.read()

            # Array with number of times DNA strings are repeated
            actual = [get_max(s, seq) for seq in DNAsequences]

        print_match(reader, actual)


if __name__ == '__main__':
    main()