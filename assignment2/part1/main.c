#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hexdump.h"

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
