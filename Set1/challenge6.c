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

    unsigned char* input1="HU";
    unsigned char* input2="If";
    printf("Test Input 1 = %s \nTest Input 2 = %s\n", input1, input2);
    printf("Hamming Distance = %d\n", hammingDistanceByte(input1, input2, 2));

    unsigned int minKeyLength=atoi(argv[2]);
    unsigned int maxKeyLength=atoi(argv[3]);
    decryptVigenereCipher(argv[1], minKeyLength, maxKeyLength);

}   