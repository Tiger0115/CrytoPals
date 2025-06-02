#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "myFunctions.h"

/*Compile and Run Commands From Challenge - 
 *
 *gcc challenge6.c -o break
 *./break
 *
 *Expected Output - 
 * 
*/

/*challenge6.c -
 *
 *@arguments - 
 *@prints - 
*/
int main(int argc, char* argv[])
{
    if(argc!=4)
    {
        printf("Error in Argument count \n");
        return -1;
    }

    unsigned char* input1="this is a test";
    unsigned char* input2="wokka wokka!!!";
    printf("Test Input 1 = %s \nTest Input 2 = %s\n", input1, input2);
    printf("Hamming Distance Test = %d\n", hammingDistanceByte(input1, input2, 14));

    char* result =malloc(4);
    char* base="TWFu";
    base64ToByte(base, result);
    result[3]='\0';

    printf("\nBase64 to Byte Test - \nInput = %s \nOutput = %s\n\n", base ,result);

    free(result);
    // free(base);

    unsigned int minKeyLength=atoi(argv[2]);
    unsigned int maxKeyLength=atoi(argv[3]);
    decryptVigenereCipher(argv[1], minKeyLength, maxKeyLength);

}   