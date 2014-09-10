
#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void){
   float change;
   int count = 0;
    do{
        printf("O hai! How much change is owed?\n");
        change = GetFloat();
        change *= 100;
        int converting = roundf(change);
        while(converting >= 25){
            count++;
            converting -= 25;
        }
        while(converting >= 10){
            count++;
            converting -= 10;
        }
        while(converting >= 5){
            count++;
            converting -= 5;
        }
        while(converting >= 1){
            count++;
            converting -= 1;
        }
        
        printf("%d\n", count);
    } while((change < 0) );
}
