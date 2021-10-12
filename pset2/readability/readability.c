#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int count_words(string text);
int count_sentences(string text);
int count_letters(string text);

int main(void)
{
    string text = get_string("Text: ");
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);
    //sentences per 100 words.
    float s = (sentences / (float)(words)) * 100;
    //letters per hundred words.
    float l = (letters / (float)(words)) * 100;
    //Coleman-Liau index for the readability test.
    float index = 0.0588 * l - 0.296 * s - 15.8;
    if (round(index) < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (round(index) >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", (int)(round(index)));
    }

}


//counts total number of letters in the entered text.
int count_letters(string text)
{
    int count = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            count += 1;

        }
    }
    return count;
}


//counts total number of words in the entered text.
int count_words(string text)
{
    int count = 1; //to consider no space at the end of the sentence.
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isspace(text[i]))
        {
            count += 1;

        }
    }
    return count;
}

//counts total sentences in the entered text.
//considering ?,! and . as the end of a sentence.
int count_sentences(string text)
{
    int count = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == '!' || text[i] == '?' || text[i] == '.')
        {
            count += 1;
        }
    }
    return count;
}