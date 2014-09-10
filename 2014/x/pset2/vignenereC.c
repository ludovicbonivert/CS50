#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>

bool keySuccessful = false;
string key = "";
int keylength = 0;
string plainText = "";
int plainText_length;
int key_count = 0;
char caesar(char token, int key);

int main(int argc, string argv[]) {
    do{
  
        if(argc != 2) {
            printf("Invalid entry \n");
            return 1;
        }
        else if(argv[1]){
            int length = strlen(argv[1]);
            for(int i = 0; i < length; i++){
                if(!isalpha(argv[1][i])){
                    printf("Your input invalid chars.\n");
                    return 1;
                }
                else{
                    keySuccessful = true;
                    key = argv[1];
                }
            }
        }
    } while(!keySuccessful);
    
   
    int keycodes[keylength];
    keylength = strlen(key);
    
    for(int i = 0; i < keylength;i++)
    {
        keycodes[i] = toupper(key[i]) - 65;
    }

    plainText = GetString();
    plainText_length = strlen(plainText);

    for (int i = 0; i < plainText_length; i++){
        if(!isalpha(plainText[i]))
        {
            printf("%c", plainText[i]);
        }
       
        else{
            printf("%c", caesar(plainText[i], keycodes[key_count]));  
            if(key_count < keylength - 1){
                key_count++;
            }
            else{
                key_count = 0;
            }
        }
    }
    printf("\n");
    return 0;
}
char caesar(char token, int key){
    if(islower(token)){
        return ((((token - 97)+key)%26)+97);
    }else{
        return ((((token - 65)  +key)%26)+65);
    }
}
