#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @author Yeury Galva Liriano
 * @date February 22, 2021
 * @brief readBinFile function reads a binary file
 * @details This function is useful to differentiate between what kind of files are being read
 * @param fileName Pointer to the file that will be attempted to be open
 */
void readBinFile(const char* fileName);

/**
 * @author Yeury Galva Liriano
 * @date February 23, 2021
 * @brief hexToBitString function changes a hex value to an 8 long bit string
 * @details 
 * @param fileName Pointer to the file that will be attempted to be open
 */
void hexToBitString(unsigned char bufferByte, int* bitString, int bitLen);

void printBinResult(int* bitString, int bitLen);

void binToInstructions(int* bitString);
void binToTargetRegisters(int* bitString);
void binToSourceRegisters(int* bitString);

void masterFunc(unsigned char* buffer, long fSize);

int main(int argc, char* argv[]) {
    // error handeling
    if (argc != 2) {
        printf("Usage: %s <FileName>\n", argv[0]);
        return 1;
    }
    char* fileName = argv[1];
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
    // this function calls all the other helper functions
    // it is the combination of all functions into 1
    masterFunc(buffer, fSize);
}

void hexToBitString(unsigned char bufferByte, int* bitString, int bitLen) {
    for (int j=0; j<bitLen; j++) {
        bitString[7-j] = (bufferByte >> j) & 1;
    }
    // printBinResult(bitString, bitLen);
}


// void printBinResult(int* bitString, int bitLen) {
//     for(int n = 0; n <bitLen; n++) {
//         // printf("%d", bitString[n]);
//     }
//     printf(" ");
// }

void binToInstructions(int* bitString) {
    if (bitString[0] == 0 && bitString[1] == 0) printf("add ");
    else if (bitString[0] == 0 && bitString[1] == 1) printf("sub ");
    else if (bitString[0] == 1 && bitString[1] == 0) printf("lw ");
    else printf("sw ");
}

void binToTargetRegisters(int* bitString) {
    if (bitString[2] == 0 && bitString[3] == 0 && bitString[4] == 0) printf("$S0, ");
    else if (bitString[2] == 0 && bitString[3] == 0 && bitString[4] == 1) printf("$S1, ");
    else if (bitString[2] == 0 && bitString[3] == 1 && bitString[4] == 0) printf("$S2, ");
    else if (bitString[2] == 0 && bitString[3] == 1 && bitString[4] == 1) printf("$S3, ");
    else if (bitString[2] == 1 && bitString[3] == 0 && bitString[4] == 0) printf("$T0, ");
    else if (bitString[2] == 1 && bitString[3] == 0 && bitString[4] == 1) printf("$T1, ");
    else if (bitString[2] == 1 && bitString[3] == 1 && bitString[4] == 0) printf("$T2, ");
    else printf("$T3, ");
}

void binToSourceRegisters(int* bitString) {
    if (bitString[5] == 0 && bitString[6] == 0 && bitString[7] == 0) printf("$S0 ");
    else if (bitString[5] == 0 && bitString[6] == 0 && bitString[7] == 1) printf("$S1 ");
    else if (bitString[5] == 0 && bitString[6] == 1 && bitString[7] == 0) printf("$S2 ");
    else if (bitString[5] == 0 && bitString[6] == 1 && bitString[7] == 1) printf("$S3 ");
    else if (bitString[5] == 1 && bitString[6] == 0 && bitString[7] == 0) printf("$T0 ");
    else if (bitString[5] == 1 && bitString[6] == 0 && bitString[7] == 1) printf("$T1 ");
    else if (bitString[5] == 1 && bitString[6] == 1 && bitString[7] == 0) printf("$T2 ");
    else printf("$T3 ");
}

void masterFunc(unsigned char* buffer, long fSize) {
    // length of the bit string ex: 00001010
    int bitLen = 8;
    // allocate memory to hold bitString 8 bit string
    int* bitString = (int*)malloc(sizeof(int)*bitLen); // 8 because it is an 8 long bit string
    for (int i=0; i<fSize; i++) {
        printf("%02x ", buffer[i]);
        hexToBitString(buffer[i], bitString, bitLen);
        binToInstructions(bitString);
        binToTargetRegisters(bitString);
        binToSourceRegisters(bitString);
        printf("\n");
    }
    // free allocated memory
    free(buffer);
    free(bitString);
}