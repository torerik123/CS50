# Get user input
while True:
    try:
        text = input("Text: ")
        if text == "":
            continue
        
    # Asks user for input again if input is not a string
    except ValueError:
        continue

    # Breaks loop if input is an int
    else:
        break

# Counts number of letters, excluding punctutation, exclamation points and question marks  
letters = 0
for count in text:
    if count.isalnum() == True:
        letters += 1

# Count words
words = 1
for word in text:
    if word == " ":
        words += 1

# Count sentences. Any punctuation mark, exclamation point or question mark counts as a sentence.
sentences = 0
for sentence in text:
    if sentence in [".", "!", "?"]:
        sentences += 1

# Calculate grade level
l = (float(letters) / float(words)) * 100
z = (float(sentences) / float(words)) * 100

index = (0.0588 * l) - (0.296 * z) - 15.8
grade = round(index)

# Output grade level
if grade > 16:
    print("Grade 16+\n")
    
elif grade < 1:
    print("Before Grade 1\n")
    
else:
    print(f"Grade {grade}\n")
