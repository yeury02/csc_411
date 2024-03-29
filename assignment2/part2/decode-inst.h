
/*
 * Author: Yeury Galva Liriano
 * Date: February 28, 2021
 * Description: Header file for creating help functions on dealing with binary files
*/

#ifndef DECODE_H
#define DECODE_H

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



#endif