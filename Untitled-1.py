
combo = [5,5,5]
words = [0,1]
length = 4
combo = [words[0]] * (length - len(combo)) + combo
print(combo)