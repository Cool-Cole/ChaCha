//
// Created by cole on 5/18/21.
//

#ifndef HEX_H
#define HEX_H

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdint.h>

char *binToHex(const uint8_t byteArray[], const size_t byteArrayLen);

uint8_t *hexToBin(const char hexKey[], const size_t hexLen);

//C++ guard
#ifdef __cplusplus
}
#endif


#endif //HEX_H
