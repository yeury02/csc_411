#include <stdio.h>
#include <stdlib.h>

void hexToBin(unsigned char byte, int* binary) {
    for(int n = 0; n < 8; n++)
        binary[7-n] = (byte >> n) & 1;
    /* print result */
    for(int n = 0; n < 8; n++)
        printf("%d", binary[n]);
}

void binToMIPS(int* binary){
    // get instruction
    if (binary[0] == 0 && binary[1] == 0){
        printf("add ");
    }

    if (binary[0] == 0 && binary[1] == 1){
        printf("sub ");
    }

    if (binary[0] == 1 && binary[1] == 0){
        printf("lw ");
    }

    if (binary[0] == 1 && binary[1] == 1){
        printf("sw ");
    }

    // get target register
    if (binary[2] == 0 && binary[3] == 0 && binary[4] == 0){
        printf("$S0 ");
    }

    if (binary[2] == 0 && binary[3] == 0 && binary[4] == 1){
        printf("$S1 ");
    }

    if (binary[2] == 0 && binary[3] == 1 && binary[4] == 0){
        printf("$S2 ");
    }

    if (binary[2] == 0 && binary[3] == 1 && binary[4] == 1){
        printf("$S3 ");
    }

    if (binary[2] == 1 && binary[3] == 0 && binary[4] == 0){
        printf("$T0 ");
    }

    if (binary[2] == 1 && binary[3] == 0 && binary[4] == 1){
        printf("$T1 ");
    }

    if (binary[2] == 1 && binary[3] == 1 && binary[4] == 0){
        printf("$T2 ");
    }

    if (binary[2] == 1 && binary[3] == 1 && binary[4] == 1){
        printf("$T3 ");
    }

    // get source register
    if (binary[5] == 0 && binary[6] == 0 && binary[7] == 0){
        printf("$S0 ");
    }

    if (binary[5] == 0 && binary[6] == 0 && binary[7] == 1){
        printf("$S1 ");
    }

    if (binary[5] == 0 && binary[6] == 1 && binary[7] == 0){
        printf("$S2 ");
    }

    if (binary[5] == 0 && binary[6] == 1 && binary[7] == 1){
        printf("$S3 ");
    }

    if (binary[5] == 1 && binary[6] == 0 && binary[7] == 0){
        printf("$T0 ");
    }

    if (binary[5] == 1 && binary[6] == 0 && binary[7] == 1){
        printf("$T1 ");
    }

    if (binary[5] == 1 && binary[6] == 1 && binary[7] == 0){
        printf("$T2 ");
    }

    if (binary[5] == 1 && binary[6] == 1 && binary[7] == 1){
        printf("$T3 ");
    }
}

int main (int argc, char *argv[]) {
  // check arguments

  // initialize variables
  FILE * f;
  long f_size;
  unsigned char * buffer;
  size_t reader;

  // open file
  f = fopen ( argv[1] , "rb" );
  if (f==NULL) {
    fputs ("File Error: Empty Binary",stderr); 
    exit (1);
  }

  // get file size
  fseek (f , 0 , SEEK_END);
  f_size = ftell (f);
  rewind (f);

  // allocate buffer
  buffer = (char*) malloc (sizeof(char)*f_size);
  if (buffer == NULL) {
    fputs ("Memory error",stderr); 
    exit (2);
  }

  // copy to buffer
  reader = fread (buffer,1,f_size,f);
  if (reader != f_size) {
    fputs ("Reading error",stderr); 
    exit (3);
  }

  // read buffer of hex output
  for (long i = 0; i < f_size; i++){
      int binary[8];
      printf("%02x ", buffer[i]);
      hexToBin(buffer[i], binary);
      printf(" ");
      binToMIPS(binary);
      printf("\n");
  }

  printf("\n");

  // terminate and buffer
  fclose (f);
  free (buffer);
  return 0;
}