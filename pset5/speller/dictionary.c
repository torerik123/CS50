// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include "dictionary.h"
#include <ctype.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned long N = 150000;

// Hash table
node *table[N];

// Cursor
node *cursor;

// Node for linked list
node *new_node;

// Wordcount
int wordcount = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Hash word
    int hashvalue = hash(word);

    // Traverse linked list
    cursor = NULL;
    cursor = table[hashvalue];

    // Keep moving until cursor == NULL
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }

        else
        {
            cursor = cursor->next;
        }
    }
    
    return false;
}

// Hashes word to a number
// djb2 hash function from http://www.cse.yorku.ca/~oz/hash.html
unsigned int hash(const char *word)
{
    // Length of word + 1 to store \0 character
    int x = strlen(word) + 1;

    // Declare array to store lowercase letters and pointer to the array
    char lowercase[x];
    char *p;

    // Make word lowercase before hashing
    for (int i = 0; i < x; i++)
    {
        lowercase[i] = tolower(word[i]);
    }

    // p points to lowercase
    p = lowercase;

    // Hash word
    unsigned int hash = 5381;
    int c = 0;

    while ((c = *p++))
    {
        hash = ((hash << 5) + hash) + c;
    }
    
    return hash % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Open dictionary file
    FILE *file = fopen(dictionary, "r");

    // Check if return value is NULL and return false if it is
    if (file == NULL)
    {
        return false;
    }

    else
    {
        // Load words into hash table to store dictionary:
        // Temp array for reading words
        char dict_word[LENGTH + 1];

        // Read strings from file, one at a time
        while (fscanf(file, "%s", dict_word) != EOF)
        {
            // Allocate space for node to store word found by fscanf
            new_node = malloc(sizeof(node));
            new_node->next = NULL;
            if (new_node == NULL)
            {
                unload();
                return false;
            }
            
            // Increase word count
            wordcount++;

            // Hash word to obtain hash value
            unsigned int hashvalue = hash(dict_word);

            // Copy word into new_node
            strcpy(new_node->word, dict_word);

            // If hash table is empty and does not point to any nodes
            if (table[hashvalue] == NULL)
            {
                table[hashvalue] = new_node;
                new_node->next = NULL;
            }
              
            else
            {
                // Set new node as head of list:
                // Point new_node->next to first element in table
                new_node->next = table[hashvalue];

                // Point head of linked list to new node
                table[hashvalue] = new_node;
            }
        }
    }
        
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (wordcount != 0)
    {
        return wordcount;
    }

    else
    {
        return 0;
    }
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        // Cursor points to first element in list
        cursor = NULL;
        cursor = table[i];

        // Unload nodes until cursor = NULL, e.g. the list is empty
        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    
    return true;
}
