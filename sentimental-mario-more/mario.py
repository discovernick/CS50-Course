# Get User Input

while True:
    try:
        height = int(input("Height: "))
        if (height > 0 and height < 9):
            break
    except:
        print("enter an integer maaaaatteeee!")

for y in range(1, height+1):
    # Print Spaces
    i = 0
    while (i < height - y):
        print(" ", end="")
        i += 1

    # Print Blocks
    i = 0
    while (i < y):
        print("#", end="")
        i += 1

    # Print Central Spaces
    print("  ", end="")

    # Print Blocks again
    i = 0
    while (i < y):
        print("#", end="")
        i += 1

    # Now actially print a new line
    print("")