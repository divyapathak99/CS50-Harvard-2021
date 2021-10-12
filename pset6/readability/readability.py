import cs50
import string


def main():
    text = cs50.get_string("Text: ")
    letters = count_letters(text)
    words = count_words(text)
    sentences = count_sentences(text)
    # sentences per 100 words.
    s = (sentences / words) * 100
    # letters per hundred words.
    l = (letters / words) * 100
    # Coleman-Liau index for the readability test.
    index = 0.0588 * l - 0.296 * s - 15.8
    Index = round(index)
    if Index < 1:
        print("Before Grade 1", end="\n")
    elif Index >= 16:
        print("Grade 16+", end="\n")
    else:
        print(f"Grade {Index}", end="\n")

# counts total number of letters in the entered text.


def count_letters(text):
    count = 0
    for i in range(len(text)):
        if (text[i].isalpha()):
            count += 1
    return count


# counts total number of words in the entered text.

def count_words(text):
    count = 1  # To consider no space at the end of the sentence.
    for i in range(len(text)):
        if text[i].isspace():
            count += 1
    return count

# counts total sentences in the entered text.
# considering ?,! and . as the end of a sentence.


def count_sentences(text):
    count = 0
    for i in range(len(text)):
        if (text[i] == '!' or text[i] == '?' or text[i] == '.'):
            count += 1
    return count


main()