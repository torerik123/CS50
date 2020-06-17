# Asks for user input
while True:
    try:
        dollars = float(input("Change: "))
        if dollars < 0:  # if not a positive int print message and ask for input again
            continue

    # Asks user for input again if input is not a number
    except ValueError:
        continue

    # Breaks loop if input is an int
    else:
        break

# Multiply dollars by 100, Round cents to nearest penny
cents = round(dollars * 100)

# Remainder counts how much change is left after quarters, nickels, dimes, or pennies have been subtracted
remainder = cents
counter = 0

while remainder > 0:
    
    # Quarters
    if (remainder - 25 > -1):
        remainder = remainder - 25
        counter += 1
    
    # Dimes
    elif (remainder - 10 > -1):
        remainder = remainder - 10
        counter += 1
        
    # Nickels
    elif (remainder - 5 > -1):
        remainder = remainder - 5
        counter += 1
    
    # Pennies
    elif (remainder - 1 > -1):
        remainder = remainder - 2
        counter += 1
    
    else:
        break
    
print(counter)