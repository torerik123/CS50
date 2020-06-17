
# Asks for user input
while True:
    try:
        n = int(input("Height: "))

    # Asks user for input again if input is not a number
    except ValueError:
        continue

    # Breaks loop if input is an int
    else:
        break

# Checks if input is in correct range
while n < 1 or n > 8:
    n = int(input("Height: "))


def printboxes(h):
    for i in range(h):              # Height = vertical columns.
        for j in range(h):          # Rows
            if i + j < h - 1:
                print(" ", end="")  # Prints spaces
            else:
                print("#", end="")  # Prints hashes
        print("\n", end="")         # Adds newline


printboxes(n)
