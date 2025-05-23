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

        line[strcspn(line, "\n")] = '\0'; 

        char* hexResult= vigenereCipher(line, key, keyPointer);
        keyPointer=((getLength(line)+1)%keyLength);

        printf("%s\n", hexResult);
        
    }

    fclose(fptr);
    free(line);
}