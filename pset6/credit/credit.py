import cs50


def main():
    x = cs50.get_int("card number: ")
    n = digit(x)
    summ = type1(x) + type2(x)
    # Initial two digits of card number.
    start_dts = int(x / 10 ** (n - 2))
    # first digit of card number.
    start_dts1 = int(x / 10 ** (n - 1))
    if (summ % 10) == 0:
        if (n == 15 and (start_dts == 34 or start_dts == 37)):
            print("AMEX", end="\n")
        elif (n == 16 and (start_dts == 51 or start_dts == 52 or start_dts == 53 or start_dts == 54 or start_dts == 55)):
            print("MASTERCARD", end="\n")
        elif ((n == 13 or n == 16) and start_dts1 == 4):
            print("VISA", end="\n")
        else:
            print("INVALID", end="\n")
    else:
        print("INVALID", end="\n")


# 1. Calculate checksum.
# 1.1 step 1. Multiplying every other digit of "card number" by 2, starting with 2nd to last digit.
def type1(x):
    text = str(x)
    d = 0
    for i in range(len(text) - 2, -1, -2):
        a = 2 * int(text[i])
        for j in str(a):
            d += int(j)
    return d

# 1.2 step 2: Sum of the digits of "card number" that weren't multiply by 2.


def type2(x):
    text = str(x)
    a = int(text[len(text) - 1])
    for i in range(len(text) - 3, -1, -2):
        a += int(text[i])
    return a

# calculate number of digits in "card number".


def digit(x):
    text = str(x)
    a = len(text)
    return a
    
    
main()