#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    if (argc != 3) {
        printf("Wrong amount of arguments: <FileName> <N>\n");
        return 1;
    }
    // turns string to int
    int N = atoi(argv[2]);
    if (N <= 0) {
        printf("N must be greater than 0\n");
        return 1;
    }
    
    FILE *fp = fopen(argv[1], "rb");
    // check if file sucessfuly opened
    if (fp == NULL) {
        perror("Error opening file: \n");
        return 1;
    }

    // obtain file size:
    fseek (fp, 0 , SEEK_END);  // moving position of pointer to end
    long fSize = ftell (fp);        // gets size of file in bytes
    rewind (fp);               // resets the pointer to the beginning

    // printf("%ld\n", fSize);

     // allocate memory to contain the whole file:
    char* buffer = (char*) malloc (sizeof(char)*fSize);
    // if no memory was allocated
    if (buffer == NULL) {
        fputs ("Memory error",stderr); 
        exit (2);
    }

    // copy the file into the buffer:
    size_t result = fread (buffer,1,fSize,fp);
    if (result != fSize) {
        fputs ("Reading error",stderr); 
        exit (3);
    }

    // printf("%ld\n", result);

    // for(int i = 0; i<result; i++)
    //     printf("\n");
    //      for(int j = 0; j<N; j++) {
    //           printf("%d ", buffer[j]); // prints a series of bytes
    //      }

    for(int i = 0; i<result/sizeof(char); i++)
        printf("%x\n ", (int)buffer[i]);
    // printf("%s", buffer);


    return 0;
}
