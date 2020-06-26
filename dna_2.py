from sys import argv, exit
import csv


def get_max(s, sub):
    # Calculate max nr of times substring is repeated
    # s:  ATATATTATAT
    # ans:[30201002010] # How many times does sub repeat in s
    # sub: AT

    # Make array the size of s with all values set to zero
    ans = [0] * len(s)

    # Iterate from right to left, end at -1, each step is -1
    for i in range(len(s) - len(sub), -1, -1):
        if s[i:i + len(sub)] == sub:

            # Check if we are at the end of the string
            if i + len(sub) > len(s) - 1:
                ans[i] = 1

            # If substring is found, add 1 to the value in s[i: len(sub)]
            else:
                ans[i] = 1 + ans[i + len(sub)]
    return max(ans)


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
    csv_path = argv[1]
    with open(csv_path) as csv_file:
        reader = csv.reader(csv_file)

        # Stores values of all sequences, skipping the names
        all_sequences = next(reader)[1:]

        # Open DNA string from command line argument
        txt_path = argv[2]
        with open(txt_path) as txt_file:
            s = txt_file.read()

            # Array with number of times DNA strings are repeated
            actual = [get_max(s, seq) for seq in all_sequences]

        print_match(reader, actual)


if __name__ == '__main__':
    main()