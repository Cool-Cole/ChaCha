//
// Created by cole on 5/18/21.
//

#include "hex.h"
#include <stdlib.h>
#include <string.h>

const char hex[17] = {'0' , '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', '\0'};

char *binToHex(const uint8_t byteArray[], const size_t byteArrayLen){
    //const char hex[16] = {'0' , '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

    char temp[3] = {0x00, 0x00, '\0'};

    // +1 is for the null terminator
    char *outputHex = calloc((byteArrayLen * 2) + 1, sizeof(char));

    // If malloc fails then
    if(outputHex == NULL){
        exit(1);
    }

    outputHex[0] = '\0';

    for(size_t i = 0; i < byteArrayLen; i++){
        temp[0] = hex[(byteArray[i] & 0xF0) >> 4];
        temp[1] = hex[(byteArray[i] & 0x0F)];

        strcat(outputHex, temp);
    }

    return outputHex;
}

// hexLen must not include the 0x character
uint8_t *hexToBin(const char hexKey[], const size_t hexLen){

    uint8_t *outputKey = calloc((hexLen / 2), sizeof(uint8_t));

    int byteIndex;
    int charIndex;

    for(byteIndex = 0, charIndex = 0; charIndex < hexLen; byteIndex++, charIndex += 2){
        outputKey[byteIndex] = (int)(strchr(hex, hexKey[charIndex]) - hex) << 4;
        outputKey[byteIndex] = outputKey[byteIndex] | (int)(strchr(hex, hexKey[charIndex + 1]) - hex);
    }

    return outputKey;
}
