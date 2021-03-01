#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// This function is used to read a binary file
void readBinFile(const char* fileName);
void getEvery5Bytes(unsigned char* buffer, long fileSize);
void readEvery5Bytes(unsigned char* fiveBytes, int count);
char* mask(int lastByte);
void ipAdresstoBinary(unsigned char* buffer, char* mask);
void hostRange(unsigned char* networkAddress, unsigned char* subnetMask, int lastByte);
void printSubnetMask(unsigned char* subnetMask);
unsigned char* buffer;
// this will be helpful to do bitwise AND comparison
int index_comp = 0;

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
    buffer = (char*) malloc (sizeof(char)*fSize);  // two's compliment Hint:(Unsinged)
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

void readEvery5Bytes(unsigned char* fiveBytes, int count) {
    // as long as the bytes are multiple of fives
    // otherwise ignore
    char* bits;
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
            printf("\n");
            bits = mask(fiveBytes[i]);
        } else {
            // print the first 4 bytes
            if (i == 3) printf("%d", fiveBytes[i]);
            else printf("%d.", fiveBytes[i]);
        }
    }
    // to take care of not having an extra new line at the end
    if (count == 5) {
        printf("\n");
    }
}

// number of bits in the subnet mask
char* mask(int lastByte) {
    // to store 32 long bitStrings
    char* bits = (char*)malloc(sizeof(char)*32); // subnet mask has 32 bits
    unsigned int num=0;
    // highest number of a 8bitString
    int binStartingCount=128;
    int count = 0;
    // this will be useful to calculate host Range
    int remainingZeros = lastByte - remainingZeros;
    int bufferCount = 0;
    unsigned char* networkAddress = (char*)malloc(sizeof(char)*4);
    unsigned char* subnetMask = (char*)malloc(sizeof(char)*4);

    printf("Network address: ");
 
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
            // bitwise AND comparison
            int ans = (buffer[index_comp] & num);
            // store network address
            networkAddress[bufferCount] = ans;
            // store submask
            subnetMask[bufferCount] = num;
            // to avoid an extra period at the end
            if (bufferCount == 3) {
                printf("%d", ans);
            }
            else {
                printf("%d.", ans);
            }
            bufferCount++;
            index_comp++;
            num = 0;
            binStartingCount = 128;
        }
        count++;
    }
    index_comp++;
    hostRange(networkAddress, subnetMask, lastByte);
    printSubnetMask(subnetMask);

    return bits;
}

void hostRange(unsigned char* networkAddress, unsigned char* subnetMask, int lastByte) {
    printf("\nUsable IP range: ");
    // just change the last byte of IP address to get 
    // first part of host rage
    for(int i = 0; i < 4; i++){
        unsigned char tmp;
        if (i != 3) tmp = (networkAddress[i] ^ 0x00);
        else tmp = (networkAddress[i] ^ 0x01);
        if (i == 3) printf("%d", tmp);
        else printf("%d.", tmp);
    }
    printf(" - ");
    // grab from
    for(long i = 0; i < 4; i++){
        unsigned char tmp;
        // XOR and OR bitwise operations
        if (i != 3) tmp = ((networkAddress[i] | (~subnetMask[i])) ^ 0x00);
        else tmp = ((networkAddress[i] | (~subnetMask[i])) ^ 0x01);
        if (i == 3) printf("%d", tmp);
        else printf("%d.", tmp);
    }
}
// Function prints the subnet mask
void printSubnetMask(unsigned char* subnetMask) {
    printf("\nSubnet mask:     ");
    for(int i=0; i<4; i++) {
        if (i == 3) printf("%d", subnetMask[i]);
        else printf("%d.", subnetMask[i]);
    }
    printf("\n");
}