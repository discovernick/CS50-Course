# Credit Card Verification Programme


number = 0
nDigits = 0
i = 0

# Lets get user input
# Get input from user
# AMEX = 15 digit & Starts with 34 or 37
# Mastercard = 16 digit numbers with 51, 52, 53, 54, or 55
# VISA = 13 or 16 digit numbers & Start with a 4
while True:
    number = input("Number: ")
    if (len(number) == 13 or len(number) == 15 or len(number) == 16):
        nDigits = len(number)
        break
    else:
        print("INVALID")
        exit(1)


# Iterating through each chracter
multiplied = []
added = 0
i = 0

for c in reversed(number):
    current_digit = int(c)
    if (i % 2 == 0):
        added += current_digit
    elif (i % 2 == 1):
        multiplied.append(current_digit)
    i += 1

# Multiplication First
multiplied_sum = 0
for char in multiplied:
    adj = char * 2
    if adj < 10:
        multiplied_sum += adj
    else:
        multiplied_sum += (adj % 10)
        multiplied_sum += (adj // 10)

final_sum = multiplied_sum + added
number = int(number)

if final_sum % 10:
    print("INVALID")
elif (nDigits == 15):
    if ((number // 10000000000000) == 34 or (number // 10000000000000) == 37):
        print("AMEX")
    else:
        print("INVALID")
elif (nDigits == 13):
    if ((number // 1000000000000) == 4):
        print("VISA")
    else:
        print("INVALID")
else:
    if ((number // 1000000000000000) == 4):
        print("VISA")
    elif ((number // 100000000000000) == 51 or (number // 100000000000000) == 52 or (number // 100000000000000) == 53 or (number // 100000000000000) == 54 or (number // 100000000000000) == 55):
        print("MASTERCARD")
    else:
        print("INVALID")

