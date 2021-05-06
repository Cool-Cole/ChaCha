#include <stdio.h>
#include <byteswap.h>

#include "chacha.h"

#define NUMROUNDS 20

int main() {
    // All bytes in the state are to be in the little endian order
    /*u_int32_t state[16] = {
            0x61707865, 0x3320646e, 0x79622d32, 0x6b206574, // Constants "expa" "nd 3" "2-by" "te k"
            0x00000000, 0x00000000, 0x00000000, 0x00000000, // First half of the 256 bit key
            0x00000000, 0x00000000, 0x00000000, 0x00000000, // Second half of the 256 bit key
            0x00000001, 0x00000000, 0x00000000, 0x00000000  // First 32 bits of the row are for the counter while the other 96 bits are reserved for the nonce

    };*/

    /*u_int32_t state[16] = {
            0x879531e0, 0xc5ecf37d, 0x516461b1, 0xc9a62f8a, // Constants "expa" "nd 3" "2-by" "te k"
            0x44c20ef3, 0x3390af7f, 0xd9fc690b, 0x2a5f714c, // First half of the 256 bit key
            0x53372767, 0xb00a5631, 0x974c541a, 0x359e9963, // Second half of the 256 bit key
            0x5c971061, 0x3d631689, 0x2098d9d6, 0x91dbd320  // First 32 bits of the row are for the counter while the other 96 bits are reserved for the nonce

    };*/

    /*
        ChaCha state with the key setup.

       61707865  3320646e  79622d32  6b206574
       03020100  07060504  0b0a0908  0f0e0d0c
       13121110  17161514  1b1a1918  1f1e1d1c
       00000001  09000000  4a000000  00000000
    */

    u_int32_t state[16] = {
            0x61707865, 0x3320646e, 0x79622d32, 0x6b206574, // Constants "expa" "nd 3" "2-by" "te k"
            0x03020100, 0x07060504, 0x0b0a0908, 0x0f0e0d0c, // First half of the 256 bit key
            0x13121110, 0x17161514, 0x1b1a1918, 0x1f1e1d1c, // Second half of the 256 bit key
            0x00000001, 0x09000000, 0x4a000000, 0x00000000  // First 32 bits of the row are for the counter while the other 96 bits are reserved for the nonce

    };

    u_int32_t original_state[16];

    for(u_int8_t i = 0; i < 16; i++) {
        original_state[i] = state[i];
    }

    printf("0x%08x 0x%08x 0x%08x 0x%08x\n", state[0], state[1], state[2], state[3]);
    printf("0x%08x 0x%08x 0x%08x 0x%08x\n", state[4], state[5], state[6], state[7]);
    printf("0x%08x 0x%08x 0x%08x 0x%08x\n", state[8], state[9], state[10], state[11]);
    printf("0x%08x 0x%08x 0x%08x 0x%08x\n", state[12], state[13], state[14], state[15]);

    printf("\n");

    for(u_int8_t currentRound = 0; currentRound < NUMROUNDS; currentRound += 2){
       fullRound(state);
    }

    // https://tools.ietf.org/html/rfc8439#section-2.1.1
    // Test Vector for the ChaCha Quarter Round
    for(u_int8_t i = 0; i < 16; ++i){
        state[i] = original_state[i] + state[i];
        state[i] = __bswap_32(state[i]);
    }

    //printf("0x%08x\n", __bswap_32(state[0]));

    printf("0x%08x 0x%08x 0x%08x 0x%08x\n", state[0], state[1], state[2], state[3]);
    printf("0x%08x 0x%08x 0x%08x 0x%08x\n", state[4], state[5], state[6], state[7]);
    printf("0x%08x 0x%08x 0x%08x 0x%08x\n", state[8], state[9], state[10], state[11]);
    printf("0x%08x 0x%08x 0x%08x 0x%08x\n", state[12], state[13], state[14], state[15]);
    
    printf("\n");

    printf("%08x%08x%08x%08x\n", state[0], state[1], state[2], state[3]);
    printf("%08x%08x%08x%08x\n", state[4], state[5], state[6], state[7]);
    printf("%08x%08x%08x%08x\n", state[8], state[9], state[10], state[11]);
    printf("%08x%08x%08x%08x\n", state[12], state[13], state[14], state[15]);

    printf("\n");
    
    return 0;
}
