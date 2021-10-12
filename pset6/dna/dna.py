import csv
import sys


def main():
    # check for valid command line argument
    if len(sys.argv) != 3:
        sys.exit("Usage: ")
    csv_file = []
    # open csv file and extract its data to "small"
    with open(sys.argv[1]) as file:
        reader = csv.DictReader(file)
        for row in reader:
            csv_file.append(row)
    # list containing the strs values.
    str_list = list(csv_file[1].keys())

    # convert values of str key into integers.
    for row in csv_file:
        for i in range(1, len(str_list)):
            row[str_list[i]] = int(row[str_list[i]])

    DNA = []
    # open the text file containg the DNA sample of an unknown candidate and store it in DNA.
    with open(sys.argv[2]) as file:
        reader = file.read()
        for i in reader:
            DNA.append(i)

    # this will create a list of strs of the dna sample.
    dna_str = []
    for i in range(1, len(str_list)):
        Max = str_count(DNA, str_list[i])
        dna_str.append(Max)

    i = 1
    j = len(str_list)
    not_true = 0
    # comparing the dna samples str's with the .csv file.
    for row in csv_file:
        csv_values = list(row.values())
        if(csv_values[i:j] == dna_str[:j]):
            print(row["name"])
        else:
            not_true += 1
     
    # if not found. print "No Match"        
    if not_true == len(csv_file):
        print("No match")

# this will calculate the str count.


def str_count(dna, str_list):
    li = []
    for i in str_list:
        li.append(i)
    i = 0
    j = len(str_list)
    count = 0
    Max = 0
    # checking for the largest repititive str of DNA SAMPLE FILE.
    while j < len(dna):
        if dna[i:j] == li:
            count += 1
            if count > 0:
                i += len(str_list)
                j += len(str_list)
        else:
            i += 1
            j += 1
            if count > Max:
                Max = count
            count = 0
    return(Max)


main()