#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "decode-inst.h"

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