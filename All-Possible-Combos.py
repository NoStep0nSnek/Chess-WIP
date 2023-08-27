def number_to_list(number, words):
    list_out = []
    while number:
        list_out = [number % len(words)] + list_out
        print(list_out, "list,")
        number = number // len(words)
        #print(number,"N,")
    return [words[n] for n in list_out]

def combinations(words, length):
    #print(len(words)**length)
    #numbers = xrange(len(words)**length)
    numbers = range(len(words)**length)

    for number in numbers:
        combo = number_to_list(number, words)  
        if len(combo) < length + 1:
            #print([words[0]] * (length - len(combo)), "1\n")
            #print(combo, "2\n")
            combo = [words[0]] * (length - len(combo)) + combo
            #print(combo, "3\n")
            yield combo

for a in combinations('01', 3):
    print(a)