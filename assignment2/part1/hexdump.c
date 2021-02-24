#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @author Yeury Galva Liriano
 * @date February 22, 2021
 * @brief readBinFile function reads a binary file
 * @details This function is useful to know that it is reading a binary file properly
 * @param fileName Pointer to the file that will be attempted to be open
 * @param N Second command line argument, used to pass in to printOutput for printing purposes
 */
void readBinFile(const char* fileName, int N);
/**
 * @author Yeury Galva Liriano
 * @date February 22, 2021
 * @brief Prints result in a formatted manner
 * @details This function prints output as specified on assignment
 * @param fSize number of bytes in file
 * @param buffer Temporary variable in memory which holds the content of the file
 * @param N Value passed in by the user, used to print output specified by the user
 */
void printOutput(long fSize, unsigned char* buffer, int N);

int main(int argc, char* argv[]) {
    // error handeling
    if (argc != 3) {
        printf("Usage: %s <FileName> <N>\n", argv[0]);
        return 1;
    }
    // turns string to int
    int N = atoi(argv[2]);
    if (N <= 0) {
        printf("N must be greater than 0\n");
        return 1;
    }
    char* fileName = argv[1];
    readBinFile(fileName, N);

    return 0;
}

void readBinFile(const char* fileName, int N) {

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
    // print output
    printOutput(fSize, buffer, N);
}

void printOutput(long fSize, unsigned char* buffer, int N) { 
    for (int i = 0; i < fSize; i++){
        // helps keep track of the first index of each row
        if (i % N == 0){
            // this takes care of not having an extra new line at the beginning
            if (i>0) {
                printf("\n");
            }
            // %08 allows to print 8 bit strings
            printf("%08x  ", i);
        }
        printf("%02x ", buffer[i]);
    }
    printf("\n");
    // free memory
    free(buffer);
}