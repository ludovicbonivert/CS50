//Everything is working except when I use int* for getAge !! 

#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>

//prototypes
int* getAge(void);

int main(int argc, string argv[]){
    int numberOfDolphins;
    //printf("The number of arguments is %d \n", argc);
    //only execute if argc is exactly 2
    if(argc == 2){
        numberOfDolphins = atoi(argv[1]);
        //only execute if amount of dolphins is higher than zero
        if(numberOfDolphins > 0){
            // make an array of dolphins of length of the number
            int* arrayOfDolphins[numberOfDolphins];
            // make variable to store age of oldest dolphin
            int oldestDolphin = 1;
            // for each dolphin, call getAge
            for(int i = 0; i < numberOfDolphins; i++){
                arrayOfDolphins[i] = getAge();
            }
            // Check for oldest dolphin
            for(int i = 0; i < numberOfDolphins; i++){
                if(oldestDolphin < *arrayOfDolphins[i]){
                    oldestDolphin = *arrayOfDolphins[i];
                }
            }
            return  printf("The oldest dolphin is %d \n", oldestDolphin);
        }else{
            return 1;
        }
    }
}

int* getAge(void){    
    printf("Please enter an age for this dolphin \n");
    int* age = malloc(sizeof(int));
    *age = GetInt();
    
    while(*age < 0){
       *age = GetInt();
    }
    
    return age;
}
