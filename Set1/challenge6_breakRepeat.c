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

    // char* input1="this is a test";
    // char* input2="wokka wokka!!!";
    // char* bin1=asciiToBinary(input1);
    // char* bin2=asciiToBinary(input2);
    // printf("%d\n", computeHammingDistanceOfBinary(bin1, bin2));

    

    int minKeySize=findKeysizeWithSmallestHammingDistance(argv[1], 2, 40);

    printf("min = %d\n", minKeySize);

    FILE* fptr=fopen(argv[1], "r");
    if (!fptr) 
    {
        perror("Error opening file");
        return -1;
    }

    fseek(fptr, 0, SEEK_END);
    int length = ftell(fptr);  // Get the size
    rewind(fptr);

    char* fileData= malloc(length+1);
    fread(fileData, 1, length, fptr);
    
    // printf("%s len \n",fileData);

    int blocklength=(length+minKeySize)/minKeySize;
    for(int i=0;i<minKeySize;i++)
    {
        char* block=malloc(blocklength+1);
        int index=0;
        
        for(int j=i;j<length;j=j+minKeySize)
        {
            block[index]=fileData[j];
            index++;
        }

        // printf("%s \n \n", block);

        char* keyString=malloc(blocklength+1);
        

    
        for(int i=0;i<blocklength;i++)
        {
            keyString[i]=key[keyPointer];
            // printf("%c", keyString[i]);
            keyPointer=++keyPointer%keyLength;
        }
        // printf("\n %d \n", keyPointer);
        keyString[lineLength]='\0';
        // printf("\n%d \n", getLength(keyString));
        char* keyBinary= asciiToBinary(keyString);

        free(block);
    }

    free(fileData);
    fclose(fptr);


    return 1;

}