import cs50

# prompt user for the height of the pyramid. height should be between (1,8)
height = cs50.get_int("Height: ")

# asking user to enter height again if its not in between (1,8)
while (height < 1 or height > 8):
    height = cs50.get_int("Height: ")

# create patern vertically.
for i in range(1, height + 1):
    l = height - i
    for j in range(0, l):
        print(" ", end="")
    # k loop will create horizontal pressure.
    for k in range(0, 2 * i):
        if k == i:
            print("  ", end="")
        print("#", end="")
    print("\n", end="")
