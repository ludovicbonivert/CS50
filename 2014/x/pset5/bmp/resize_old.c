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
        /*
        OLD FORMULAS
        // Determine old padding
        int pitch_old = biWidth_old * 3;
        if (pitch_old % 4 != 0){
            pitch_old += 4 - (pitch_old % 4);
        }
        int padding_old = pitch_old - (biWidth_old * 3);

        // Determine new padding
        int pitch = bi.biWidth * 3; // 3 since it's 24 bits, or 3 bytes per pixel 
        if (pitch % 4 != 0){ 
            pitch += 4 - (pitch % 4); 
        } 
        int padding = pitch - (bi.biWidth * 3); // this is how many bytes of padding you need
        */

        // determine padding for scanlines
        int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
        
        //Sometimes Height is negative ??
        if(bi.biHeight < 0){
            bi.biHeight *= -1;
        }

        // Each byte has 3 bytes of value so * RGBTRIPLE
        // padding * bi.biHeight because for each row you add padding
        bi.biSizeImage = bi.biHeight * bi.biWidth * sizeof(RGBTRIPLE) + (padding * bi.biHeight); 
        bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER); // + 54 for the headers
        
        // write outfile's BITMAPFILEHEADER
        fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

        // write outfile's BITMAPINFOHEADER
        fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

        // make an array of pixels. We are going to save each row of pixels
        RGBTRIPLE saveHorizontalPixels [biWidth_old];

        for(int i = 0, biHeight = abs(biHeight_old); i < biHeight; i++){
            RGBTRIPLE triple;
            for(int j = 0; j < biWidth_old; j++){
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                // repeat fwrite for n times
                for(int k = 0; k < n; k++){
                   fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
                // Save each pixel into an array so we can duplicate it n times
                // cannot set saveHorizontalPixels into k loop because it will not update j
                saveHorizontalPixels[j] = triple;
            }

           	// skip over padding if any
            // INFILE
            fseek(inptr, padding_old, SEEK_CUR);
            // and add it back in the OUTFILE
            for(int k = 0; k < padding; k++){
                    fputc(0x00, outptr);
            }
            // NEW CODE
            /* 
				WHILE RowToCopy is not 0 copy again horizontally on next line (== vertically resizing)
				How to reposition fseek at the start of a row ?
            */
			int rowsToCopy = n ;
			while(rowsToCopy != 0){
				for(int m = 0; m < biWidth_old; m++){
					fseek(inptr, -(bi.biWidth + padding), SEEK_CUR);   
                	for(int k = 0; k < n; k++){
                		
                    	fwrite(&saveHorizontalPixels[m], sizeof(RGBTRIPLE), 1, outptr);
 	                }
            	}
				rowsToCopy--;
			}

			/*
			for(int m = 0; m < biWidth_old; m++){   
                for(int k = 0; k < n; k++){
                    fwrite(&saveHorizontalPixels[m], sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            */
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
