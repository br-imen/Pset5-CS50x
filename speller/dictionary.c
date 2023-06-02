// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;


// TODO: Choose number of buckets in hash table
const unsigned int N = 5381;  //it was 26

// Hash table
node *table[N];

// a global variable to track how many words in dictionnary
int track = 0;

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    // return toupper(word[0]) - 'A';


    /////////////////////////////////////
    unsigned long hash_value = 0xabcdefULL;
    int copy_c;
    for (int i = 0; i < strlen(word); i++)
    {
        copy_c = (int)word[i];
        if (word[i] >= 65 && word[i] <= 90)
        {
            copy_c = copy_c + 32;
        }

        hash_value = (hash_value * (unsigned long)copy_c) & 0xffffffULL;
    }
    unsigned long int_hash_value = hash_value % N;
    return int_hash_value;
}


// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    unsigned int index_output = hash(word);

    node *trav = table[index_output];

    while (trav != NULL)
    {

        if (strcasecmp(trav->word, word) == 0)
        {
            return true;
        }
        else
        {
            trav = trav->next;
        }

    }

    return false;

}


// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    //fopen the dictionary
    FILE *source = fopen(dictionary, "r");
    if (source == NULL)
    {
        printf("Source can't be open");
        return 1;
    }

    //to store the word from the source
    char *store_word = malloc(sizeof(char) * (LENGTH + 1));
    if (store_word == NULL)
    {
        printf("Error. Allocation was unsuccessful. \n");
        return 1;
    }

    //copy word by word from source (dictionary) into a buffer store_word until it reaches the end of source.
    while (fscanf(source, "%s", store_word) != EOF)
    {
        //create a new node
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            printf("can't malloc a new node");
            return 1;
        }

        //copy the word from the array to the node
        strcpy(new_node->word, store_word);

        //hash the word in the new node to have an index
        unsigned int index_input = hash(new_node->word);

        //insert the new node in the hashtable[index]:
        new_node->next = table[index_input];
        table[index_input] = new_node;

        // track is global variable to track insertion of new node for size function
        track++;
    }
    fclose(source);
    free(store_word);

    return true;
}


// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    if (track > 0)
    {
        return track;
    }
    else
    {
        return 0;
    }
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    node *tmp = NULL;
    node *curr = NULL;

    for (int p = 0 ; p < N ; p++)
    {
        curr = table[p];
        while (curr != NULL)
        {
            tmp = curr->next;
            free(curr);
            curr = tmp;
        }
    }

    return true;
}

