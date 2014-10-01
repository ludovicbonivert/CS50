/**
 * resize.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * 
 */
       
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }
    int n = atoi(argv[1]);
    if(n < 0  || n > 100){
        printf("Resize n must be a positive integer less than or equal to 100 \n");
        return 1;
    }
    
    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }



    // Si n est plus grand que 1 nous devons effectuer tout les changements, sinon ne pas resize
    if(n > 1){
        // save old data
        LONG biWidth_old = bi.biWidth;
        LONG biHeight_old = bi.biHeight;

        // Determine old padding
        int padding_old = (4 - (biWidth_old * sizeof(RGBTRIPLE)) % 4) % 4;
        // Change information about bitmapfileheader & bitmapinfoheader accordingly n-times
        bi.biHeight *= n; 
        bi.biWidth *= n; 

        // determine padding for scanlines
        int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
        
        //Sometimes Height is negative ??
        bool heightWasChanged = false;
        if(bi.biHeight < 0){
            bi.biHeight *= -1;
            heightWasChanged = true;
        }

        // Each byte has 3 bytes of value so * RGBTRIPLE
        // padding * bi.biHeight because for each row you add padding
        bi.biSizeImage = bi.biHeight * bi.biWidth * sizeof(RGBTRIPLE) + (padding * bi.biHeight); 
        bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER); // + 54 for the headers
        
        
        // if height was made positive we set it back to negative
        if(heightWasChanged == true){
            bi.biHeight *= -1;
        }
        // write outfile's BITMAPFILEHEADER
        fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

        // write outfile's BITMAPINFOHEADER
        fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

        
        for(int i = 0, biHeight = abs(biHeight_old); i < biHeight; i++){
            RGBTRIPLE triple;

            //reinitialize value when we come again in that horizontal loop
            int rowsToResize = n;
            //Calculate the start of a row in bytes
            int returnToStart = (biWidth_old*sizeof(RGBTRIPLE)+padding_old);
            // While rowsToResize isn't less than 1 keep writing the same pixels of the reading row
            while(rowsToResize != 0){
                for(int j = 0; j < biWidth_old; j++){
                    fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                    // repeat fwrite for n times
                    for(int k = 0; k < n; k++){
                       fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                    }
                }
               	// skip over padding if any
                // INFILE
                fseek(inptr, padding_old, SEEK_CUR);
                // and add it back in the OUTFILE
                for(int k = 0; k < padding; k++){
                    fputc(0x00, outptr);
                }
                rowsToResize--;
                // Do we need to put fseek at the start of the actual row ? 
                if(rowsToResize > 0){
                    fseek(inptr, -(returnToStart), SEEK_CUR);
                }else {
                    //continue to next line
               }
            }  
        }

        // close infile
        fclose(inptr);

        // close outfile
        fclose(outptr);


    }
    //if resize == 1 , just do a simple copy of the file
    else if(n == 1){
        // write outfile's BITMAPFILEHEADER
        fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

        // write outfile's BITMAPINFOHEADER
        fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

        // determine padding for scanlines
        int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

        // iterate over infile's scanlines
        for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++){
            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++){
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }

            // skip over padding, if any
            fseek(inptr, padding, SEEK_CUR);

            // then add it back (to demonstrate how)
            for (int k = 0; k < padding; k++){
                fputc(0x00, outptr);
            }
        }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks 
    }
    
    return 0;
}
