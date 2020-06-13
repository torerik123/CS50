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

// Number of buckets in hash table // change this value after loading dict works
const unsigned int N = 676;

// Hash table
node *table[N];

// Wordcount
int wordcount = 0;

// Returns true if word is in dictionary else false -//SOMETHING IN HERE IS WRONG
bool check(const char *word)
{
    //  Hash word
    int hashvalue = hash(word);

    //  Access linked list at table[hashvalue]
    node *linkedlist = table[hashvalue];

    //Traverse linked list
    //Set cursor to first item in table[hashvalue]
    node *cursor = &linkedlist[0];

    //Keep moving until cursor == NULL
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            cursor = cursor->next;
            return true;
        }
    }
    return false;
}

// Hashes word to a number
// djb2 hash function from http://www.cse.yorku.ca/~oz/hash.html

unsigned int hash(const char *word)
{
    //  Make word lowercase before hashing
    int x = strlen(word) + 1;
    char *lowercase = malloc(x * sizeof(int));

    for (int i = 0; i < x; i++)
    {
        lowercase[i] = tolower(word[i]);
    }

    //  Hash word
    unsigned int hash = 5381;
    int c = 0;

    while ((c = *lowercase++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash % N;
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

        //  Temp array for reading words - old char dict_word[LENGTH + 1];
        char dict_word[LENGTH + 1];

        //  Read strings from file, one at a time. fscanf will return EOF once it reaches end of file
        while(fscanf(file, "%s", dict_word) != EOF) //EOF or 1 or 0????
            {
                //  Allocate space for node to store word found by fscanf
                node *new_node = malloc(sizeof(node));
                if (new_node == NULL)
                {
                    unload();
                    return EOF;
                }

                //  Copy word into node
                strcpy(new_node->word, dict_word);
                new_node->next = NULL;

                //  Increase word count
                wordcount++;

                //  Hash word to obtain hash value
                unsigned int hashvalue = hash(dict_word);

                //  Initialize hash table
                for (int i = 0; i < N; i++)
                {
                    table[i] = NULL;
                }

                //  If hash table is empty and does not point to any nodes
                if (table[hashvalue] == NULL)
                {
                        //  Insert node into hash table
                        table[hashvalue] = new_node;
                        new_node->next = NULL;
                }

                else
                {
                    //  Set new node as head of list:
                    //  Point to first element in table
                    new_node->next = table[hashvalue];

                    //  Point table[hashvalue] to new node
                    table[hashvalue]->next = new_node;
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
        //  Cursor points to first element in list
        node *cursor = table[i];

        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    return true;
    }

    return false;
}
