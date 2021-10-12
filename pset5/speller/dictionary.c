// Implements a dictionary's functionality
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <strings.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 1;
int count_word = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int hash_int = hash(word);
    node *curser = table[hash_int];
    while (curser != NULL)
    {
        if (strcasecmp(word, curser->word) == 0)
        {
            return true;
        }
        else
        {
            curser = curser->next;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int hash_int = 0;
    unsigned int key_len = strlen(word);
    for (int i = 0; i < key_len; i++)
    {
        hash_int = hash_int + 37 * tolower(word[i]);
    }
    hash_int = hash_int % N;
    return hash_int;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // open a dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)

    {
        printf("can't open the file\n");
        return false;
    }
    char dict_word[LENGTH + 1];
    while (fscanf(file, "%s", dict_word) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;

        }
        strcpy(n->word, dict_word);
        n->next = NULL;
        int hash_index = hash(dict_word);

        if (table[hash_index] == NULL)
        {
            table[hash_index] = n;
        }
        else
        {
            n->next = table[hash_index];
            table[hash_index] = n;
        }
        count_word += 1;
    }

    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // count_word is the count of how many times the word loaded in the table from in the load function.
    return count_word;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < sizeof(table); i++)
    {
        node *temp = table[i];
        node *curser = table[i];
        while (curser != NULL)
        {
            curser = curser->next;
            free(temp);
            temp = curser;
        }
    }
    return true;
}
