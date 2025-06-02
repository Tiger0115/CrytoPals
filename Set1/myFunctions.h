#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


unsigned char* hexadecimalToBase64(const char* input);
void hexadecimalToRawBytes(const char* hexInput, unsigned char* rawBytes);
unsigned char hexCharToByte(unsigned char c);
void xorOfRawBytes(const unsigned char* input1, const unsigned char* input2, unsigned int len, unsigned char* result);
void rawByteToHex(const char* byte, unsigned char* result, unsigned int byteLength);
unsigned int englishCheck(unsigned char* input, double threshold);
void singleByteXorWithByte(unsigned char* byte, unsigned int byteLength);
void singleByteXorWithHex(const char* input);
void fileSingleByteXorWithHex(const char* filename, unsigned int lineSize);
void fileRepeatingKeyXorByte(const char* filename, unsigned int lineSize, const char* key, unsigned int removeNewLine);
int repeatingKeyXorByte(const char* line, unsigned int lineSize, const char* key, unsigned int keyPointer, unsigned char* result);
void xorOfTwoByteStrings(const char* byte1, const char* byte2, unsigned char* result);
unsigned int repeatingKeyMaker(const char* key, unsigned char* repeatingKey, unsigned int repeatingKeyLength, unsigned int keyPointer);
unsigned int hammingDistanceByte(unsigned char* byte1, unsigned char* byte2, unsigned int length);
void decryptVigenereCipher(const char* filename, unsigned int minKeyLength, unsigned int maxKeyLength);
unsigned int getMinKeyLength(const char* block, unsigned int minKeyLength, unsigned int maxKeyLength);
unsigned int base64ToByte(const char* base64, unsigned char* byteResult);
unsigned int base64ToIntLookUpTable(char c);
void getEveryNmodMPosition(const char* block, unsigned char* subBlock, unsigned int blockLength, unsigned int subBlockLength, unsigned int pos, unsigned int num);

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
            // in case we exceed the remaining bits, we add padding.
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
void rawByteToHex(const char* byte, unsigned char* result, unsigned int byteLength)
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
 *@param char* filename - char array of filename 
 *       int lineSize - length of hexadecimal line.
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

/*fileRepeatingKeyXorByte - takes a filepath to char list and xors each line with key
 *                          We use repeating key XOR.
 *                          Example - if key is 'ICE', he first byte of plaintext will be XOR'd against I, the next C, the next E, then I again for the 4th byte, and so on
 *
 *@param char* filename - char array of filename
 *       int maxLineSize - maximum length of line in the file
 *       char* key - char array containing the key
 *       int removeNewLine - flag value, should be one if '\n' needs to be removed
 *       
 *@note - the result will be printed in the terminal and wont be returned.     
*/
void fileRepeatingKeyXorByte(const char* filename, unsigned int maxLineSize, const char* key, unsigned int removeNewLine)
{
    FILE *fptr=fopen(filename,"r");
    if(!fptr)
    {
        printf("Error in opening file\n");
        return;
    }

    unsigned char* line=malloc(maxLineSize+2); // because there is "\n" at the end of line
    unsigned int lineSize=maxLineSize;
    unsigned int keyPointer=0;
    while(fgets(line, maxLineSize+2, fptr))
    {
        if(removeNewLine==1)
            line[strcspn(line,"\n")]='\0';

        lineSize=strlen(line);
        unsigned char* result=malloc(lineSize+1);
        
        keyPointer=repeatingKeyXorByte(line, lineSize, key, keyPointer, result);
        result[lineSize]='\0';

        unsigned char* resultHex=malloc((lineSize*2)+1);
        rawByteToHex(result, resultHex, lineSize);

        printf("%s \n", resultHex);
        free(resultHex);
        free(result);
    }

    free(line);
    fclose(fptr);
}

/*repeatingKeyXorByte - takes a plaintext as char array and xors it with key
 *                          We use repeating key XOR.
 *                          Example - if key is 'ICE', he first byte of plaintext will be XOR'd against I, the next C, the next E, then I again for the 4th byte, and so on
 *
 *@param char* line - char array of plaintext
 *       int lineSize - length of plaintext, i.e. of line
 *       char* key - char array containing the key
 *       int keyPointer - index of starting point of the key, helps when there are multiple lines of plaintext but we are encypting it as a astream
 *       char* result - empty char array which has the same size as line.
 *
 *@assumption - result was allocated the same memory as line
 * 
 *@returns the index of next key pointer 
*/
int repeatingKeyXorByte(const char* line, unsigned int lineSize, const char* key, unsigned int keyPointer, unsigned char* result)
{
    unsigned char* repeatingKey=malloc(lineSize+1);
    keyPointer=repeatingKeyMaker(key, repeatingKey, lineSize ,keyPointer);
    repeatingKey[lineSize]='\0';

    xorOfTwoByteStrings(line, repeatingKey, result);

    free(repeatingKey);
    return keyPointer;

}

/*xorOfTwoByteStrings - takes a byte char array and xors it with another byte char array
 *
 *@param char* byte1 - first byte char array
 *       char* byte2 - second byte char array
 *       char* result - empty char array which has the same size as byte1.
 *
 *@assumption - result was allocated the same memory as byte1
 * 
 *@note this function does not return anything and the xor value is stored in result.
*/
void xorOfTwoByteStrings(const char* byte1, const char* byte2, unsigned char* result)
{
    unsigned int length=strlen(byte1);

    for(int i=0;i<length;i++)
    {
        result[i]=byte1[i] ^ byte2[i];
    }    
}

/*repeatingKeyMaker - for the given key, it makes a repeating key 
 *
 *@param char* key - char array containing the key
 *       char* repeatingKey - empty char array which is alloted the size of repeatingKeyLength.
 *       int repeatingKeyLength - length of required repeating key
 *       int keyPointer - index of starting point of the key, helps when there are multiple lines of plaintext but we are encypting it as a astream
 * 
 *@returns the index of next key pointer 
*/
unsigned int repeatingKeyMaker(const char* key, unsigned char* repeatingKey, unsigned int repeatingKeyLength, unsigned int keyPointer)
{
    unsigned int keyLength= strlen(key);
    for(int i=0;i<repeatingKeyLength;i++)
    {
        repeatingKey[i]=key[keyPointer];
        keyPointer=(keyPointer+1)%keyLength;
    }
    return keyPointer;
}

unsigned int hammingDistanceByte(unsigned char* byte1, unsigned char* byte2, unsigned int length)
{
    unsigned int sum=0;

    for(int i=0;i<length;i++)
    {
        //the below line works. It is inbuilt for gcc but not my logic
        // sum += __builtin_popcount(byte1[i] ^ byte2[i]);

        unsigned int temp=(unsigned int)(byte1[i] ^ byte2[i]);

        while(temp!=0)
        {
            if(temp%2)
                sum++;

            temp>>=1;
        }
    }

    return sum;
}

void decryptVigenereCipher(const char* filename, unsigned int minKeyLength, unsigned int maxKeyLength)
{
    FILE* fptr=fopen(filename, "r");
    if (!fptr) 
    {
        perror("Error opening file");
        return;
    }

    fseek(fptr, 0, SEEK_END);
    int length = ftell(fptr);  // Get the size
    rewind(fptr);


    unsigned char* block=malloc(length+1);
    fread(block, 1, length, fptr);
    block[length]='\0';

    printf("block length = %d\n", strlen(block));
    
    unsigned int byteLength=(strlen(block)*6)/8;
    unsigned char* block_byte=malloc(byteLength+1);

    byteLength=base64ToByte(block, block_byte);
    block_byte[byteLength]='\0';

    printf("%d %s\n",strlen(block_byte), block_byte);
    unsigned int minKey=getMinKeyLength(block_byte, minKeyLength, maxKeyLength);

    printf("min key = %d\n", minKey);

    unsigned int subBlockLength=(byteLength+minKey-1/minKey);
    unsigned char* key=malloc(minKey+1);
    for (int i = 0; i < minKey; i++) 
    {
        unsigned char* subBlock = malloc(subBlockLength + 1);
        getEveryNmodMPosition(block_byte, subBlock, byteLength, subBlockLength, i, minKey);

        unsigned char bestChar = 0;
        double bestScore = 0.0;

        for (int k = 0; k < 128; k++) {
            unsigned char* result = malloc(subBlockLength + 1);
            for (int j = 0; j < subBlockLength; j++) {
                result[j] = subBlock[j] ^ (char)k;
            }
            result[subBlockLength] = '\0';

            double score = englishCheck(result, 0.99);  // or your scoring function
            if (score > bestScore) {
                bestScore = score;
                bestChar = (char)k;
            }
            free(result);
        }

        key[i] = bestChar;
        free(subBlock);
    }
key[minKey] = '\0';
printf("Recovered key: %s\n", key);


    free(block);
    fclose(fptr);

}

unsigned int getMinKeyLength(const char* block, unsigned int minKeyLength, unsigned int maxKeyLength)
{
    unsigned int minHammingDist=1000;
    unsigned int minKey=1000;
    for(int i=minKeyLength;i<=maxKeyLength;i++)
    {
        unsigned char* block1=malloc(i+1);
        unsigned char* block2=malloc(i+1);
        
        memcpy(block1, block, i);
        memcpy(block2, block+i, i);

        // printf("%d %s %s\t", i, block1, block2);
        
        block1[i]='\0';
        block2[i]='\0';
        
        unsigned int temp=hammingDistanceByte(block1, block2, i);
        // printf("%d\n", temp);
        if(temp<minHammingDist)
        {
            minHammingDist=temp;
            minKey=i;
        }
    }

    return minKey;
}

unsigned int base64ToByte(const char* base64, unsigned char* byteResult)
{
    /*
    This was a bit complicated to write so i am writing pseudocode - 

    len= length of base64
    index= iterator for byteResult
    i= iterator for base64

    while i<length
        if ith element of base64 is newline 
            then move on to next element
        
        set[4]= set of 4 base64 element that we need to make 3  bytes
        count = keeps track of 4 elements

        while we stay in limits
            if the ith element of base64 is not newline
                then count element of set is ith element of base64
                increment count if we satisfy if condition

            increment i regardless we pass if condition or not
        
        if count is not 4 then we had wrong number of elements

        padding= the number of "=" padding characters present in set

        if last or last two element are padding we count padding

        val= 0 // we add 3 bytes of data to val
        for iterating on set from 0 to 3
            left shift val by 6 bits, initially it is 0 so makes no difference for first time. in other cases adds 6 0's
            perform OR operation with the base64 int value of characters. as such the values are copied to last 6 bits of val..

        // depending on paddig we add elements to byteResult
        we left shift val by 16 bits to keep only the leftmost 8 bits and perform AND with 0xFF(255) to keep only the leftmost 8 bits elements
        we left shift val by 8 bits to keep only the leftmost 16 bits and perform AND with 0xFF(255) to remove the leftmost 8 bits so we are only left with middle 8 bits
        we left shift val by 0 bits(which doesnt change val)and perform AND with 0xFF(255) to keep only rightmost 8 bits;


    */
    int len=strlen(base64);

    int index=0;
    int i=0;
    while(i<len)
    {        
        if(base64[i]=='\n' || base64[i]=='\r') 
        {
            i++;
            // byteResult[index++]='\n';
            continue;
        }

        char set[4];
        int count=0;
        
        while(count<4 && i<len)
        {
            if(base64[i]!='\n' && base64[i]!='\r')
            {
                set[count++]=base64[i];
            }
            i++;
        }

        if(count<4) 
            break;
  
        unsigned int padding=0;
        
        if (set[2] == '=' && set[3] == '=')
            padding = 2;
        else if (set[3] == '=')
            padding = 1;

        unsigned int val=0;
        for(int j=0;j<4;j++)
        {
            val<<=6;
            val|=base64ToIntLookUpTable(set[j]);
        }

        if(padding==0)
        {
            byteResult[index++]=(val>>16) & 0xFF;
            byteResult[index++]=(val>>8) & 0xFF;
            byteResult[index++]=(val>>0) & 0xFF;
        }
        else if(padding==1)
        {
            byteResult[index++]=(val>>16) & 0xFF;
            byteResult[index++]=(val>>8) & 0xFF;
        }
        else if(padding==2)
        {
            byteResult[index++]=(val>>16) & 0xFF;
        }
        
        
    }

    return index;
    
}

unsigned int base64ToIntLookUpTable(char c)
{    
    if ('A' <= c && c <= 'Z') return (int)(c - 'A') ;
    if ('a' <= c && c <= 'z') return (int)(c - 'a') + 26;
    if ('0' <= c && c <= '9') return (int)(c - '0')+52;
    if('+'==c) return 62;
    if('/'==c) return 63;
    if('='==c) return 0;
    return 0;
}

void getEveryNmodMPosition(const char* block, unsigned char* subBlock, unsigned int blockLength, unsigned int subBlockLength, unsigned int pos, unsigned int num)
{
    int subBlockIndex=0;
    for(int i=0;i<blockLength;i++)
    {
        if(i%num==pos && subBlockIndex<subBlockLength)
        {
            subBlock[subBlockIndex++]=block[i];
        }
    }
    subBlock[subBlockIndex] = '\0';
}