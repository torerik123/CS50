// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table // change this value after loading dict works
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    
    return 0;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    //  Open dictionary file
        FILE *file = fopen(dictionary, "r");

    //  Check if return value is NULL and return false if it is
    if (file == NULL)
    {
        return false;
    }

    else
    {
        //  Load words into hash table to store dictionary:

        //  Temp array for reading words
        char dict_word[LENGTH + 1];

        //  Read strings from file, one at a time. fscanf will return EOF once it reaches end of file
        while(fscanf(file, "%s", dict_word) != EOF)
            {
                //  Allocate space for word node
                node *new_node = malloc(sizeof(node));
                if (new_node == NULL)
                {
                    return false;
                }
                    
                //  Copy word into node
                strcpy(new_node->word, dict_word);
                new_node->next = NULL;

                //  Hash word to obtain hash value
                // Hash function currently returns zero
                unsigned int hashvalue = hash(dict_word);

                //  Insert node into hash table
                //  If table[hashvalue] is empty
                if (table[hashvalue] == NULL)
                {
                        table[hashvalue] = new_node;
                        new_node->next = NULL;
                }
                
                else
                {
                    // Set new node as head of list:
                    //  Point to first element in table
                    new_node->next = table[hashvalue];
                    
                    //  Point table[hashvalue] to new node
                    table[hashvalue]->next = new_node;    
                }
            }
    }
        return true;

}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    return false;
}
