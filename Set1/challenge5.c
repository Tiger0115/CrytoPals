#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "myFunctions.h"

/*Compile and Run Commands From Challenge - 
 *
 *gcc challenge5.c -o five
 *./five 5.txt ICE 42
 *
 *Expected Output - 
 * 0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272a282b2f2043
 * 0a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f
*/

/*challenge5.c - takes a file containing plaintext and xors it with given key using repeating key xor
 *
 *@arguments - filename, key, maximum length of a line(does not include newline i.e. '\n')
 *@prints - ciphertext in hexadecimal format
*/
int main(int argc, char* argv[])
{
    if(argc!=4)
    {
        printf("Error in Argument count \n");
        return -1;
    }

    int length=atoi(argv[3]);

    fileRepeatingKeyXorByte(argv[1], length, argv[2], 0);
}   