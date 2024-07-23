// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>
#include <stdio.h>


#include "dictionary.h"

int word_count = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 18278;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    node* ptr = table[hash(word)];
    while (ptr != NULL)
    {
        if (strcasecmp(ptr->word, word) == 0)
        {
            return true;
        }
        ptr = ptr->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int hash = 0;

    if (word[1] == '\0')
    {
        hash = (tolower(word[0]) - 'a');
    }

    else if (word[2] == '\0')
    {
        for (int i = 0; i < 2; i++)
        {
            hash =(hash * 26 + (tolower(word[i]) - 'a'));
        }
        hash += 26;
    }
    else
    {
        for (int i = 0; i < 3; i++)
        {
            hash =(hash * 26 + (tolower(word[i]) - 'a'));
        }
        hash += 702;
    }

    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *source = fopen(dictionary, "r");

    if (source == NULL)
    {
        printf("Error loading dictionary.");
        return false;
    }
    char word[46];
    int index;
    while (fscanf(source, "%s", word) != EOF)
    {
        word_count++;
        node *n = malloc(sizeof(node));

        if (n == NULL)
        {
            return false;
        }

        strcpy(n -> word, word);
        index = hash(word);
        n -> next = table[index];
        table[index] = n;
    }

    fclose(source);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *tmp;
        node *ptr = table[i];
        while (ptr != NULL)
        {
            tmp = ptr -> next;
            free(ptr);
            ptr = tmp;
        }
    }
    return true;
}
