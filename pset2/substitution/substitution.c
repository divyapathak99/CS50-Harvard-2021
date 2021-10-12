#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include<math.h>

void encrypt(string text, string key);
int main(int argc, string argv[])
{
    int count = 0;
    if (argc == 2)
    {
        int count1 = 0;
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            if (isalpha(argv[1][i]))
            {
                for (int j = i + 1 ; j < n; j++)
                {
                    if (argv[1][i] == argv[1][j])
                    {
                        count = 1; // count turns 1 if alphabet repeats.
                    }
                }
            }
            else
            {
                count1 = 1;
                
            }
            
        }
        //check if the key is valid, means it must contains only letters and must be 26 in numbers, no repeated alphabets.
        if (count1 == 0 && strlen(argv[1]) == 26 && count == 0)
        {
            //ask user for the plaintext to be encrupt.
            string plaintext = get_string("plaintext: ");
            encrypt(plaintext, argv[1]);
            return 0;
            
        }
        else
        {
            //if the key is not valid return
            printf("passcode not valid!\n");
            return 1;
            
        }
        
    }
    else
    {
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }
}

//converting plaintext into ciphertext.
void encrypt(string text, string key)
{
    string word =  "abcdefghijklmnopqrstuvwxyz";
    string WORD =  "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    printf("ciphertext: ");
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        //if text contains only letters then do this.
        if (isalpha(text[i]))
        {
            for (int j = 0, m = strlen(word); j < m; j++)
            {
                //if plaintext is uppercase convert it into correspoding uppercase cyphertext.
                if (isupper(text[i]))
                {
                    if (WORD[j] == text[i])
                    {
                        printf("%c", toupper(key[j]));

                    }

                }
                //if plaintext is lowercase convert it into correspoding lowercase cyphertext.
                else if (islower(text[i]))
                {
                    if (word[j] == text[i])
                    {
                        printf("%c", tolower(key[j]));

                    }

                }

            }
        }
        //else print the text as it is. (like ',' '!' etc.)
        else
        {
            printf("%c", text[i]);

        }

    }
    printf("\n");
}


