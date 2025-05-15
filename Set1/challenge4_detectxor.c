#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "myFunctions.h"

int main(int argc, char* argv[])
{
    if(argc!=2)
    {
        printf("Error in Argument count \n");
        return -1;
    }

    FILE* fptr=fopen(argv[1], "r");
    if (!fptr) {
        perror("Error opening file");
        return -1;
    }

    char* line=malloc(64);

    
    int i =0;
    char* xorString= malloc(61);
    xorString[60]='\0';
    while(fgets(line, 64, fptr))
    {
        line[strcspn(line, "\n")] = '\0'; 

        char* binary = hexadecimalToBinary(line);       

        char* ascii = binaryToAscii(binary);
        

        // printf("%d:\nASCII   = %s\n\n", i++,  ascii);

        
        for(int k=0;k<256;k++)
        {
            for(int j=0;j<60;j++)
            {
                xorString[j]=(char)k;
            }

            char* xorStringBinary = asciiToBinary(xorString);
            char* result = xorOfBinary(binary, xorStringBinary);

            char* resultAscii =binaryToAscii(result);
            if(englishCheck(resultAscii)==1)
            {
                printf("i=%d k= %d   %s \n", i, k, resultAscii );
            }

            // free(xorString);
            free(result);
            free(resultAscii);
            
        }
        i++;

            free(binary);
            free(ascii);
    

            
        
    }

    fclose(fptr);

    free(xorString);
    free(line);
}