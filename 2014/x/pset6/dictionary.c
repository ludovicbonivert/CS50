/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>
#include "dictionary.h"
#define LISTLENGTH 24

/* Implementing node for a word */
typedef struct node{
	char word[LENGTH+1];
	struct node* next;
}node;

/* prototype hash funciton */
int hashfunction(const char* key);

// Keep track of the number of words in the dictionary. Increments in the load function
int numberOfWordsInDictionary = 0;

/*Global variable for our dictionary */
// Our hash list will be equal to an array of 24, there are 24 letters in our alphabet
// I initialize each array item to NULL so that we can check if it is later still NULL or not
node* hashList[LISTLENGTH] = {NULL};

// global variable for the head of the list
// It is an array because each list in the array will have is own head
node* head[LISTLENGTH] = {NULL};

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // TODO
    // First, hash the word. the hash function returns an int. that int will be our search index into our hashtable
    int value = hashfunction(word);
    node* tmp = hashList[value];
    // Traverse the whole hashTable for the given word

    while(tmp != NULL){
    	// insensitive compare
    	int result = strncasecmp(tmp->word, word, 50);

    	if(result == 0){
    		return true;
    	}else {
    		// cursor needs to go to the next word
    		if(tmp->next != NULL){
    			tmp = tmp->next;
    		}else{
    			// hashList[value] (tmp) doesn't have a next so word isn't in list
    			return false;
    		}
    	}

    }
    return false;
}   

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // TODO
    //open the dictionary
    FILE* input = fopen(dictionary, "r");
    if(input == NULL){
    	printf("Could not open %s \n", dictionary);
    	fclose(input);
    	return 2;
    }

	// make a new node
    node* new_word = malloc(sizeof(node));

    // while there are words to hash into dictionary
    while(fscanf(input, "%s", new_word->word) != EOF){
    	// I create here a new pointer. It's this pointer that I'm going to add to the hashTable

    	node* wordToAdd = malloc(sizeof(node));
    	strcpy(wordToAdd->word, new_word->word);

    	// hash each word (key) and get the value back. The value is the emplacement where the key will be stored
    	int value = hashfunction(new_word->word);
    	// if the hashlist[value] is NULL (empty) we can directly append our node to it
    	if(hashList[value] == NULL){
    		//printf("hashList[value] is threated like a null value !");
    	}
    	if(hashList[value] == NULL){
    		hashList[value] = wordToAdd;
    		head[value] = wordToAdd;

    	}
    	// else we need to append it at the start of the list but care of not losing the other elements!
    	else{
    		wordToAdd->next = head[value];
    		head[value] = wordToAdd;
    		hashList[value] = wordToAdd;
    	}
    // We need to keep track of each new word in our dictionary for the size function
    numberOfWordsInDictionary++;
    }			
    free(new_word);
    fclose(input);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    return numberOfWordsInDictionary;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{	
	
	int i = 0;
	// While we are not at the end of our hashtable
	while(i != LISTLENGTH+1){
		if(head[i] != NULL){
			node* cursor = head[i];
			// ok head is not null so there are nodes that we must free
			// we need to traverse the whole linked list and free each one of them
			// take care of not losing track of the linked list ! 
			while(cursor != NULL){

				node* tmp = cursor;
				cursor = cursor->next;
				free(tmp);

			}
			free(cursor);
		i++;	
		}else {
			// head is null so we only need to free that actual emplacement and go to
			// the next emplacement
			free(hashList[i]);
			i++;
		}
	}
	
    return true;
}

int hashfunction(const char* key){
	int value = toupper(key[0]) - 'A';
	return value % LISTLENGTH;
}
