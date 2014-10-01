/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Recovers JPEGs from a forensic image.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

typedef uint8_t BYTE;

/*
    psudo:
    Open memory card file : ok
    Find beginning of jpg 
*/

int main(int argc, char* argv[])
{
    FILE* file = fopen("card.raw", "r");
    if(file == NULL){
    	printf("Could not open card.raw file");
    	return 2;
    }
    //Initialize a buffer
    BYTE block[512];
    bool newJpg = false;
    bool append = false;
    int count = 0;
    char title[50];
    //While we can read (we are not at the EOF)
    while(fread(block, sizeof(block), 1, file)){
    	// Searching for a star block

        //beginning of a jpg
        if(block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && block[3] == 0xe0){
    		newJpg = true;
    		append = false;
    	}
    	//beginning of a jpg
    	else if(block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && block[3] == 0xe1){
    		newJpg = true;
    		append = false;
    	}
    	// If we found a star block we need to create a new img
    	if(newJpg == true){
    		//FILE* image = fopen("img.jpg", "w");
            if(count >= 10){
                sprintf(title, "%d%d.jpg", 0,count);    
            }else {
                sprintf(title, "%d%d%d.jpg", 0,0,count);
            }
            
            FILE* image = fopen(title, "w");
            count++;
 			if(image == NULL){
 				printf("Could not create a new img");
 				return 3;
 			}	
 			fwrite(block, sizeof(block), 1, image);
 			fclose(image);
 			append = true;
            newJpg = false;
    	}else if(append == true){
            FILE* image = fopen(title, "a");
            fwrite(block, sizeof(block), 1, image);
            fclose(image);
        }
        // first time it will write 2 times
    	
 		//fclose(image);


    }
    //close file
    fclose(file);

    //succesful end
    return 0;
}

