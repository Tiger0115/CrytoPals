#include <stdio.h>
#include <stdlib.h>
#include <string.h>


unsigned char* hexadecimalToBase64(const char* input);
void hexadecimalToRawBytes(const char* hexInput, unsigned char* rawBytes);
unsigned char hexCharToByte(unsigned char c);


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

void hexadecimalToRawBytes(const char* hexInput, unsigned char* rawBytes)
{
    int len=strlen(hexInput)/2;
    for(int i=0;i<len; i++)
    {
        rawBytes[i]=(hexCharToByte(hexInput[i*2])<<4) | hexCharToByte(hexInput[(i*2)+1]);
    }
}

unsigned char hexCharToByte(unsigned char c)
{
    if ('0' <= c && c <= '9') return c - '0';
    if ('A' <= c && c <= 'F') return c - 'A' + 10;
    if ('a' <= c && c <= 'f') return c - 'a' + 10;
    return 0;
}

