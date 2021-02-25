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

/**
 * @author Yeury Galva Liriano
 * @date February 25, 2021
 * @brief Prints result in a formatted manner
 * @details This function prints output as specified on assignment
 * @param buffer Temporary variable in memory which holds the content of the file
 * @param N Size of file in bytes
 */
void printResults(unsigned char* buffer, long fileSize);

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
    // prints results
    printResults(buffer, fSize);
    // terminate
    free(buffer);
}

void printResults(unsigned char* buffer, long fileSize) {
    char opCodes[4][4] = {"add", "sub", "lw", "sw"};
    char instructions[8][4] = {"$S0", "$S1", "$S2", "$S3", "$T0", "$T1", "$T2", "$T3"};
    
    int opcode, inst1, inst2;
    for (long i = 0; i < fileSize; i++) {   
        // Here I do bitwise operations and right shifting
        opcode = (buffer[i] & 0xC0) >> 6;
        inst1 = (buffer[i] & 0x38) >> 3;
        inst2 = (buffer[i] & 0x07);
        printf("%s %s, %s\n", opCodes[opcode], instructions[inst1], instructions[inst2]);
    }
}