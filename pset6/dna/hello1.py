from cs50 import get_string


# = get_string("whats your name: ")
#print(f"hello, {ans}")
#class student():
    #def __init__(self, name, id):
        #self.name = name

        #self.id = id

    #def changeID(self, id):
     #   self.id = id
    #def print(self):
     #   print("{}-{}".format(self.name, self.id))
#jane = student("jane ", 10)
#jane.print()
#jane.changeID(11)
#jane.print()
dna = []
    # open the text file containg the DNA sample of an unknown candidate and store it in DNA.
with open("sequences/1.txt") as file:
    reader = file.read()
    for i in reader:
        dna.append(i)

str_list = 'TATC'
li = []
for i in str_list:
    li.append(i)


i = 0
j = len(str_list)
count = 0
Max = 0
dna1 = dna[i:j]
while j < len(dna):
    dna1 = dna[i:j]
    print(dna1)
    if dna1 == li:
        print(dna1 == li)
        count += 1
        print(count)
        if count > 0:
            i += len(str_list)
            j += len(str_list)
    else:
        i += 1
        j += 1
        if count > Max:
            Max = count
        count = 0
print(Max)