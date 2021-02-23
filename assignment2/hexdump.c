#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hexdump.h"

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
            printf("\n");
            printf("%08x  ", i);
        }
        printf("%02x ", buffer[i]);
    }
    printf("\n");
    // free memory
    free(buffer);
}


// int tmp = 0;
        // int j = 0;
        // int tracker = 0;
        // for(int i = 0; i<(result/sizeof(unsigned char)); i++) {
        //     printf("\n");
        //     j = 0;
        //     if (tmp == result) {
        //         break;
        //     }
        //     printf("%08x ", tmp);
        //     while(j<N) {
        //         if (tmp != result) {
        //             printf("%02x ", (int)buffer[tmp]); // prints series of bytes
        //             tmp++;
        //             j++;
        //         } else {
        //             break;
        //         }
        //     }
        // }
        // free(buffer);
