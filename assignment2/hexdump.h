/*
 * Author: Yeury Galva Liriano
 * Date: February 28, 2021
 * Description: Header file for creating help functions on dealing with binary files
*/

#ifndef HEXDUMP_H
#define HEXDUMP_H

/**
 * @author Yeury Galva Liriano
 * @date February 22, 2021
 * @brief readBinFile function reads a binary file
 * @details This function is useful to differentiate between what kind of files are being read
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


#endif