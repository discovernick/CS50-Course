# Takes in sentences and returns
def main():
    # Initialise variables
    L = 0.00
    S = 0.00
    index = 0.00

    # User Input
    matter = input("Test: ")

    # Spit Out Values
    L = (count_letters(matter) / count_words(matter)) * 100
    S = (count_sentences(matter) / count_words(matter)) * 100
    index = 0.0588 * L - 0.296 * S - 15.8

    if (index < 1):
        print("Before Grade 1")
    elif (index >= 16):
        print("Grade 16+")
    else:
        index = round(index)
        print("Grade " + str(index))

# Comments


def count_letters(words):
    counter = 0
    for c in words:
        if c.isalpha() == True:
            counter += 1

    print("letters: ", counter)
    return counter

# Comments


def count_words(words):
    counter = len(words.split())
    print("words: ", counter)
    return counter

# Comments


def count_sentences(words):
    counter = 0
    for c in words:
        if (c == "!" or c == "?" or c == "."):
            counter += 1
    print("sentences: ", counter)
    return counter


main()