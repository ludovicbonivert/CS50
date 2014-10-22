/**
 * linked.c
 *
 * week 7 section
 * fall 2013
 * 
 * practice using linked lists
 */

#include <cs50.h>
#include <stdbool.h>
#include <stdio.h>

// typedef a node for the linked list
typedef struct node
{
    int n;
    struct node* next;
}
node;

// function prototypes
bool insert_node(int value);
void print_nodes(node* list);
void free_nodes(node* list);

// global variable for the head of the list
node* head = NULL;

int main(void)
{ 
    // offer the user two options
    while (true)
    {
        printf("Please choose an option (0, 1, 2): ");
        int option = GetInt();
        
        switch (option)
        {
            // quit
            case 0:
                free_nodes(head);
                printf("Goodbye!\n");
                return 0;
            
            // insert int into linked list
            case 1:
                printf("Please enter an int: ");
                int v = GetInt();
                char* success = insert_node(v) ? "was" : "was not";
                printf("The insert %s successful.\n", success);
                break;
            
            // print all ints
            case 2:
                print_nodes(head);
                break;
            
            default:
                printf("Not a valid option.\n");
                break;
        }
    }
}

/**
 * Create a new node for a given value and insert it into a list.
 */
bool insert_node(int value)
{
    node* new_node = malloc(sizeof(node));
    if(new_node == NULL){
        printf("new_node coudn't be created");
        return false;
    }
    new_node->n = value;
    new_node->next = NULL;

    // create prev and curr pointer
    node* curr_ptr = head;
    node* prev_ptr = NULL;

    // if head is NULL, the list is empty and we can make our head linking directly to our new node
    if(head == NULL){
        head = new_node;
        return true;
    }
    // if list is not empty we need to check a few things
    while(curr_ptr != NULL){
        // insert before
        if(value < curr_ptr->n){
            new_node->next = curr_ptr;
            if(prev_ptr == NULL){
                head = new_node;    
            }else {
                prev_ptr->next = new_node;
            }
            
            return true;
        }

        if(value > curr_ptr->n){
            // need to update pointers
            prev_ptr = curr_ptr;
            curr_ptr = curr_ptr->next;
            if(curr_ptr == NULL){
                // we must be at the end of the list
                prev_ptr->next = new_node;
                curr_ptr = new_node;
                return true;
            }
        }
        if(value == curr_ptr->n){
            // value already in list
            free(new_node);
            return false;
        }
    }
    return true;
}

/**
 * Print out all of the ints in a list.
 */
void print_nodes(node* list)
{
    // I need to store head because I update it in the while loop
    node* tmp = head;
    while(head != NULL){
        printf("%d ", head->n);
        head = head->next;
    }
    head = tmp;
}

/**
 * Frees all of the nodes in a list upon exiting the program.
 */
void free_nodes(node* list)
{   
    // save previous pointer for freeing
    node* prev;
    while(head != NULL){
        prev = head;
        head = head->next;
        free(prev);
    }
}

