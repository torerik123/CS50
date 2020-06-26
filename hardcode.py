string = "AAGGTAAGTTTAGAATATAAAAGGTGAGTTAAATAGAATAGGTTAAAATTAAAGGAGATCAGATCAGATCAGATCTATCTATCTATCTATCTATCAGAAAAGAGTAAATAGTTAAAGAGTAAGATATTGAATTAATGGAAAATATTGTTGGGGAAAGGAGGGATAGAAGG"

substring = "AATG"
#"AGATC", AATG", "TATC"

STRcount = {}

#substr_count = 0

"""for i in range(len(substr)):
    start = 0
    end = len(substr[i])
    substr_count = 0
    maxcount = 0

    while True:
        loc = string.find(substr[i], start) ## Add where to end
        if loc == -1:
            break
        substr_count += 1
        start = loc + end

        if substr_count > maxcount:
            maxcount = substr_count
            print(maxcount)
            STRcount[substr[i]] = maxcount

#print(STRcount)"""

#https://stackoverflow.com/questions/61131768/how-to-count-consecutive-substring-in-a-string-in-python-3
