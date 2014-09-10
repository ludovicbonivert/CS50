#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

string caesar (string p, long long key);
int key;
string plainText;
bool success = false;

int main(int argc, string argv[]){
        do{
           if (argc != 2){
            printf("You need to submit a valid encryption key.\n");
            return 1 ;
        }else {
            key = atoi(argv[1]);
            
            plainText = GetString();
            caesar(plainText, key);
            success = true;
        } 
        }while(!success);
        
        //printf("What is the level of encryption that you want ? \n");
     return 0;   
}

string caesar (string p, long long key){
    for(int i = 0, n = strlen(p); i < n; i++){
        if(!(isalpha(p[i]))){
              p[i] =  p[i];
        }else {
            if(isupper(p[i])){
                if((p[i]+key)> 90){
                    p[i]  = (((p[i] - 65) + key)%26)+65;
                }else{
                      p[i] += key;                 
                }
            }else if(islower(p[i])){
                if((p[i]+key)> 122){
                    p[i]  = (((p[i] - 97) + key)%26)+97;
                }
                else {
                    p[i] += key; 
                }
              }  
        }
       printf("%c", p[i]); 
    }
    printf("\n");
    return p;
}
