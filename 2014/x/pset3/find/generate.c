/**
 * generate.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Generates pseudorandom numbers in [0,LIMIT), one per line.
 *
 * Usage: generate n [s]
 *
 * where n is number of pseudorandom numbers to print
 * and s is an optional seed
 */
       
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LIMIT 65536

int main(int argc, string argv[])
{
    // If the amount of arguments isn't exactly 2 or 3
    // print then the following message
    if (argc != 2 && argc != 3)
    {
        printf("Usage: ./generate n [s]\n");
        return 1;
    }

    // Save the second argument into n
    int n = atoi(argv[1]);
    
    // if the amount of parameters equals 3 
    // execute the first if statement and else execute the else block
    if (argc == 3)
    {
        srand((unsigned int) atoi(argv[2]));
    }
    else
    {
        srand((unsigned int) time(NULL));
    }

    // while i < n print every random number.
    // print n amount of random numbers pushed in the parameter
    for (int i = 0; i < n; i++)
    {
        printf("%i\n", rand() % LIMIT);
    }
    
    // that's all folks
    return 0;
}
