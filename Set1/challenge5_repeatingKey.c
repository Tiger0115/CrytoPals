#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "myFunctions.h"

int main(int argc, char* argv[])
{
    if(argc!=3)
    {
        printf("Error in Argument count \n");
        return -1;
    }

    FILE* fptr=fopen(argv[1], "r");
    if (!fptr) {
        perror("Error opening file");
        return -1;
    }

    char* line=malloc(51);
    char* key= argv[2];

    int keyLength=getLength(key);

    int keyPointer=0;
    while(fgets(line, 51, fptr))
    {
        // printf("%d \n", strcspn(line, "\n"));
        line[strcspn(line, "\n")] = '\0'; 
        line[strcspn(line, "\r")] = '\0';
        

        // printf("%d \n", getLength(line));
        int lineLength=getLength(line);
        // char* lineContent=malloc(lineLength);
        // lineContent = strdup(line);  
        char* lineContent = strdup(line);

        printf("%s \n", lineContent);
        // lineContent[lineLength]='\0';

        char* keyString=malloc(lineLength+1);
        

    
        for(int i=0;i<lineLength;i++)
        {
            keyString[i]=key[keyPointer];
            printf("%c", keyString[i]);
            keyPointer=++keyPointer%keyLength;
        }
        // printf("\n %d \n", keyPointer);
        keyString[lineLength]='\0';
        printf("\n %d \n", getLength(keyString));
        char* keyBinary= asciiToBinary(keyString);

        char* lineBinary= asciiToBinary(lineContent);
        char* xorResult= xorOfBinary(lineBinary, keyBinary);

        char* hexResult= binaryToHex(xorResult);

        printf("%s\n", hexResult);
        
        char* hexResultBinary= hexadecimalToBinary(hexResult);
        char* hexresultAscii= binaryToAscii(hexResultBinary);
        

        // printf("result = %s \n",hexresultAscii);
        // printf("len = %d \n", getLength(hexresultAscii));

        free(hexResultBinary);
        free(hexresultAscii);

        free(lineContent);

        free(lineBinary);
        free(xorResult);
        free(hexResult);
        free(keyString);
        free(keyBinary);
       
        
    }

    fclose(fptr);

    
    free(line);
    // free(key);
}