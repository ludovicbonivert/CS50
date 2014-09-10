/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>
#include <stdbool.h>
#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{  
    int start = 0;
    int end = n - 1;
    // while length of the list
    while(end >= start){
        int middle = (start+end) / 2;
        if(values[middle] == value){
            return true;
        }
        else if(value > values[middle]){
        // search right
            start = middle+1;
        }
        else if(value < values[middle]){   
        // search left
            end = middle-1;
        }
    }
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{ 
    //Bubble sort
    for(int i = 0; i < n; i++){
        if(values[i] > values[i+1]){
            int temp1 = values[i];
            int temp2 = values[i+1];
            values[i] = temp2;
            values[i+1] = temp1;
            i-=2;
        }
    }
    return;
}
