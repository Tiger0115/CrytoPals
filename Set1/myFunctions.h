#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


unsigned char* hexadecimalToBase64(const char* input);
void hexadecimalToRawBytes(const char* hexInput, unsigned char* rawBytes);
unsigned char hexCharToByte(unsigned char c);
void xorOfRawBytes(const unsigned char* input1, const unsigned char* input2, unsigned int len, unsigned char* result);
void rawByteToHex(const char* byte, char* result, int byteLength);
unsigned int englishCheck(unsigned char* input, double threshold);
void singleByteXorWithByte(unsigned char* byte, unsigned int byteLength);
void singleByteXorWithHex(const char* input);


/*hexadecimalToBase64 - converts a char array of hexadecimal to base64 format
 *
 *@param char* input- pointer to a const char array in hexadecimal format
 *
 *@return returns a char array in base64 format
*/
unsigned char* hexadecimalToBase64(const char* input)
{
    const char base64_table[]="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    
    unsigned int length=strlen(input);
    unsigned int byteLength=length/2;//since 2 hexadecimals make up one byte.
    //one hexadecimal= 4bit, one byte= 8bits

    unsigned char* rawBytes=malloc(byteLength+1);//allot memory
    hexadecimalToRawBytes(input, rawBytes);
    rawBytes[byteLength]='\0';

    unsigned int base64Length=((byteLength+2)*4)/3 ; // this will include the padding length

    unsigned char* base64=malloc(base64Length+1);
    base64[base64Length]='\0'; 

    unsigned int basePointer=0;
    for(int i=0;i<byteLength;i=i+3)
    {
        unsigned int val=0;

        int remaining=byteLength-i;

        for(int k=0;k<3;k++)
        {
            val<<=8;
            
            // we add the raw bytes to val as long as we have enough 
            // then we left shift val by 8 bits to make space for the next 8 bits
            // since initially its 0, its left shift is also 0
            if(k<remaining)
                val=val | rawBytes[i+k];
        }
        
        for(int k=0;k<4;k++)
        {
            // we right shift val by 18,12,6,0, bits to take the 6 bits at a time.
            // next we perform AND operation with 0x3F (i.e. 63) to ensure that only the last 6 bits are present 
            // in case we exceed the reamining bits, we add padding.
            if(k<remaining+1)
                base64[basePointer]=base64_table[(val>>(18- 6*k)) & 0x3F];
            else
                base64[basePointer]= '=';

            basePointer++;
        }


    }

    free(rawBytes);
    return base64;

}

/*hexadecimalToRawBytes - converts a char array of hexadecimal format of 4 bits for each number 
 *                        to byte format where each number is of 8 bits. 
 *
 *@param hexInput: pointer to char array of hexadecimal format
         rawBytes: pointer to an empty char array which will store the byte format digits 

 *@note the function returns nothing but the result will be updated in char* rawBytes
*/
void hexadecimalToRawBytes(const char* hexInput, unsigned char* rawBytes)
{
    int len=strlen(hexInput)/2;
    for(int i=0;i<len; i++)
    {
        //we rightshift the first hexadecimal digit by 4 bits then we perform "OR" with the next digit
        //example A3 = (A)1010  (3)0011
        //here - (1010 0000) OR 0011
        rawBytes[i]=(hexCharToByte(hexInput[i*2])<<4) | hexCharToByte(hexInput[(i*2)+1]);
    }
}

/*hexCharToByte - converts a char in hexadecimal format to a 4bit char 
 *                example - 'A' in hexadecimal is 10
 *                          in raw Bytes - 10 or 1010
 *
 *@param char c - a char which is in hexadecimal format
 *
 *@returns a char of 4 bits in byte format
*/
unsigned char hexCharToByte(unsigned char c)
{
    if ('0' <= c && c <= '9') return c - '0';
    if ('A' <= c && c <= 'F') return c - 'A' + 10;
    if ('a' <= c && c <= 'f') return c - 'a' + 10;
    return 0;
}

/*xorOfHexadecimal - performs xor of 2 hexadecimal char arrays
 *
 *@param char* input1 - first char array in hexadecimal format
 *       char* input2 - second char array in hexadecimal format 
 *
 *@returns an unsigned char array having result of xor of the hexadecimal
*/
unsigned char* xorOfHexadecimal(const char* input1, const char* input2)
{
    unsigned int len1=strlen(input1);
    unsigned int len2=strlen(input2);
    unsigned int byteLength=len1/2;
    unsigned char* result=malloc(byteLength+1);

    if(len1!=len2) //return empty array if lengths dont match
    {
        printf("Input lengths do not match, returning empty array \n");
        return result;
    }

    //convert input1 to raw bytes
    unsigned char* byte1=malloc(byteLength+1);
    hexadecimalToRawBytes(input1, byte1);
    byte1[byteLength]='\0';

    //convert input2 to raw bytes
    unsigned char* byte2=malloc(byteLength+1);
    hexadecimalToRawBytes(input2, byte2);
    byte2[byteLength]='\0';

    //xor of rawbytes
    xorOfRawBytes(byte1, byte2, len1/2, result);
    result[byteLength]='\0';

    free(byte1);
    free(byte2);

    //convert rawbytes to hexadecimal
    unsigned char* hexResult=malloc(len1+1);    
    rawByteToHex(result, hexResult, byteLength);
    hexResult[len1]='\0';

    free(result);
    return hexResult;

}

/*xorOfHexadecimal - performs xor of 2 byte char arrays
 *
 *@param char* input1 - first char array in byte/ascii format
 *       char* input2 - second char array in byte/ascii format 
 *       char* result - an empty array where the function stores the result
 *
 *@note the result will be stored in the result char array.
 *      Assumption - 1)result is alloted the same size as input1 and input2
 *                   2)input1 and input2 are of the same size
*/
void xorOfRawBytes(const unsigned char* input1, const unsigned char* input2, unsigned int len, unsigned char* result)
{
    for(int i=0;i<len;i++)
    {
        result[i]=input1[i] ^ input2[i];
    }
}

/*xorOfHexadecimal - converts raw bytes to hexadecimal
 *
 *@param char* byte - char array in byte/ascii format
 *       char* result - an empty array where the function stores the result
 *       int byteLength - length of byte char array
 *
 *@note the result will be stored in the result char array.
 *      Assumption - 1)result is alloted twice the size as byte                   
*/
void rawByteToHex(const char* byte, char* result, int byteLength)
{
    const char hex_table[]="0123456789abcdef";
    for(int i=0;i<byteLength;i++)
    {
        result[i*2]=hex_table[byte[i]>>4];
        result[i*2 + 1]= hex_table[(byte[i] & 0x0F)];
    }
}

/*singleByteXorWithHex - takes a hexadecimal char array and converts it to byte array
 *                       and passes it to singleByteXorWithByte to find a byte which decrypts the ciphertext
 *
 *@param char* input - char array in hexadecimal format
 *       
 *@note - the result will be printed in the terminal and wont be returned. 
 *        User has to manually select the result    
*/
void singleByteXorWithHex(const char* input)
{
    unsigned int length=strlen(input);
    unsigned byteLength=length/2;
    unsigned char* rawBytes=malloc(byteLength+1);

    hexadecimalToRawBytes(input, rawBytes);
    // rawBytes[byteLength]='\0';

    singleByteXorWithByte(rawBytes, byteLength);
    

}

/*singleByteXorWithByte - takes a byte char array and tries to XOR all possible bytes with all characters in the array 
 *                        it performs an sanity check on the ouput using the method englishCheck to filter out irrelevant results
 *                        there is an additional check where we compare the length of result and bytelength
 *
 *@param char* byte - char array in byte format
         int byteLength - length of byte array 
 *       
 *@note - the result will be printed in the terminal and wont be returned. 
 *        User has to manually select the result    
*/
void singleByteXorWithByte(unsigned char* byte, unsigned int byteLength)
{
    for(int i=0;i<128;i++)
    {
        unsigned char* result=malloc(byteLength+1);
        
        for(int j=0;j<byteLength;j++)
        {
            result[j]=byte[j] ^ (char)i;
        }

        result[byteLength]='\0';

        if(englishCheck(result, 0.99)==1 && strlen(result)>=0.9*byteLength)
        {
            printf("Iteration= %d \t Key =%c \nResult = %s \n\n",i, (char)i, result);
        }
        
        free(result);
    }
}

/*englishCheck -  performs a sanity check on the input by checking how many characters are alphabets, digits, space, punctuation
 *                the function finds the ratio of relevant characters to total characters. 
 *                If the ratio is more than threshhold then it returns 1 else it returns 0
 *
 *@param char* input - char array in byte format
 *       double threshold - threshold of ratio above which the result is acceptable. 
 *       
 *@returns unsigned int - the function returns 1 if input is above threshold else returns 0
 *
 *@note - Threshold has to be in the range 0 to 1.  
*/
unsigned int englishCheck(unsigned char* input, double threshold)
{
    int len = strlen(input);
    int printable = 0;

    for(int i = 0; i < len; i++)
    {
        char c = input[i];
        

        // Acceptable characters:
        if (isalpha(c) || isdigit(c) || isspace(c) || ispunct(c))
        {
            printable++;
        }
        else
        {
            // Reject control characters and non-printables
            if ((unsigned char)c < 32 || (unsigned char)c > 126)
                return 0;
        }
    }
    return (printable >= len * threshold) ? 1 : 0;
}

/*singleByteXorWithHex - takes a filepath to hexadecimal list and converts each line to byte array
 *                       and passes it to singleByteXorWithHex to find a byte which decrypts the ciphertext.
 *                       Tries out all combinations forall lines. 
 *
 *@param char* input - char array of filename and length of hexadecimal line.
 *       
 *@note - the result will be printed in the terminal and wont be returned. 
 *        User has to manually select the result    
*/
void fileSingleByteXorWithHex(const char* filename, unsigned int lineSize)
{
    FILE *fptr=fopen(filename,"r");
    if(!fptr)
    {
        printf("Error in opening file\n");
        return;
    }

    unsigned char* line=malloc(lineSize+2); // because there is "\n" at the end of line

    unsigned int lineNumber=1;
    while(fgets(line, lineSize+2, fptr))
    {
        line[strcspn(line,"\n")]='\0';

        printf("LineNumber = %d \n", lineNumber);

        singleByteXorWithHex((const unsigned char*)line);

        lineNumber++;
    }

    free(line);
    fclose(fptr);

}

