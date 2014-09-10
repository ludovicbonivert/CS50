#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

string caesar (string p, long long key);
long long key;
char *keys;
string plainText;
bool success = false;

int main(int argc, string argv[]){
        keys = malloc(sizeof(char)*strlen(argv[1]));
        do{
           if (argc != 2){
            printf("You need to submit a valid encryption key.\n");
            return 1 ;
        }else if(argv[i]){
        
        int length = strlen(argv[1]);
            for(int i = 0; i < length; i++)
            {
                if(!isalpha(argv[1][i]))
                {
                    
                    printf("Your input is .\n");
                    return 1;
                }
                }
        
        else{
            for(int i = 0 ; i < strlen(argv[1]); i++){
                keys[i] = argv[1][i];
                keys[i] = atoi(argv[1][i]);
            }
            int y;
            sscanf(keys, "%d", &y);
            printf("%d", y);
            plainText = GetString();
            caesar(plainText, key);
            success = true;
            free(keys);
        } 
        }while(!success);
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
