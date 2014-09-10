#include <cs50.h>
#include <stdio.h>
int main(void){
    string hash = "#";
    string space = " "; 
    int height;
    // Ask for the user input 
    do{
        printf("What is the height of the piramid ? \n");
        height = GetInt();
        if((height < 0) || (height > 23) ){
            printf("The height must be between 0 and 23 ! \n");
        }
    }while((height < 0 ) || (height > 23));
    
    
    
    for(int i = 1; i < (height+1); i++){
        for(int z = height; z > i; z--){
            printf("%s", space);
        }
        for(int y = 0; y < i; y++){
            printf("%s", hash);
        }
        printf("%s\n", hash);
    }
    
}
