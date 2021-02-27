#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @author Yeury Galva Liriano
 * @date February 22, 2021
 * @brief readBinFile function reads a binary file
 * @details This function is useful to know that it is reading a binary file properly
 * @param fileName Pointer to the file that will be attempted to be open
 */
void readBinFile(const char* fileName);

void getEvery5Bytes(unsigned char* buffer, long fileSize);
void readEvery5Bytes(unsigned char* fiveBytes, int count);
char* mask(int lastByte);
void ipAdresstoBinary(unsigned char* buffer);

int main(int argc, char* argv[]) {

    // error handeling
    if (argc != 2) {
        printf("Usage: %s <FileName>\n", argv[0]);
        return 1;
    }
    char* fileName = argv[1];
    // this function returns a dynamic array buffer
    readBinFile(fileName);

    return 0;
}

void readBinFile(const char* fileName) {

    FILE *fp = fopen(fileName, "rb");
    // check if file sucessfuly opened
    if (fp == NULL) {
        perror("Error opening file: \n");
        exit(0);
    }
    // obtain file size:
    fseek (fp, 0 , SEEK_END);  // moving position of pointer to end
    long fSize = ftell (fp);   // gets size of file in bytes
    rewind (fp);               // resets the pointer to the beginning

    // allocate memory to contain the whole file:
    unsigned char* buffer = (char*) malloc (sizeof(char)*fSize);  // two's compliment Hint:(Unsinged)
    // if no memory was allocated
    if (buffer == NULL) {
        fputs ("Memory error",stderr); 
        exit (2);
    }
    // copy the file into the buffer:
    size_t result = fread (buffer,sizeof(char),fSize,fp);
    // close file
    fclose(fp);
    if (result != fSize) {
        fputs ("Reading error\n",stderr); 
        exit (3);
    }
    getEvery5Bytes(buffer, fSize);
    // terminate
    free(buffer);
}

void getEvery5Bytes(unsigned char* buffer, long fileSize) {
    // TO TEMPORARALY store every 5 bytes
    unsigned char* fiveBytes = (unsigned char*)malloc(sizeof(unsigned char)*5); // 1 extra for null character
    // this variable will be used to keep track every 5 bytes
    int every5Count = 0;
    for (long i = 0; i < fileSize; i++) {
        // as long as I have not seen 5 bytes
        if(every5Count != 5) {
            // added it to temp array
            fiveBytes[every5Count] = buffer[i];
            every5Count++;
        } else {
            // read 5 chars at a time
            readEvery5Bytes(fiveBytes, every5Count);
            // I set to 1 rather than 0 because I would then
            // be looking at every 6 bytes rather than 0
            every5Count=1;
            // add to array starting at position 0
            fiveBytes[every5Count-1] = buffer[i];
        }
    }
    // this handles the remaining last characters
    // if file size is not multiple of 5
    readEvery5Bytes(fiveBytes, every5Count);

    free(fiveBytes);
}

char* readEvery5Bytes(unsigned char* fiveBytes, int count) {
    // as long as the bytes are multiple of fives
    // otherwise ignore
    if (count == 5) {
        printf("IP address:      ");
    }
    // read each byte at a time (max bytes = 5)
    for (int i = 0; i < count; i++) {
        // if there isn't 5 bytes
        if (count < 5) {
            break;
        // this is checking I am at the last byte of the 5 bytes
        } else if((count-1)==i) {
            // I am at the last byte
            printf("---%d---", fiveBytes[i]);
            printf("\n");
            mask(fiveBytes[i]);
        } else {
            // print the first 4 bytes
            printf("%d.", fiveBytes[i]);
        }
    }
    // to take care of not having an extra new line at the end
    if (count == 5) {
        printf("\n");
    }
}

// number of bits in the subnet mask
char* mask(int lastByte) {
    
    char* bits = (char*)malloc(sizeof(char)*32); // subnet mask has 32 bits
    int num=0;
    int binStartingCount=128;
    int count = 0;
    printf("Subnet Mask:     ");
 
    // it will always be a 32 bitstring
    for(int i=0; i<32; i++){
        // check to add 1's to array
        if(count < lastByte) {
            bits[i] = 1;
            num += binStartingCount;
            binStartingCount /= 2;
        } 
        // to add 0's to array
        if (count >= lastByte) {
            bits[i] = 0;
        }
        // to know when I have seen 8 bits
        if ((count+1)%8 == 0) {
            printf("%d.", num);
            num = 0;
            binStartingCount = 128;
        }
        count++;
    }
    return bits;
}

void ipAdresstoBinary(unsigned char* buffer) {
    

}