#include "chacha.h"
#include <stdio.h>

#define LE32(p) ( \
    ((u_int32_t)(((u_int8_t *)(p))[0]) << 0) | \
    ((u_int32_t)(((u_int8_t *)(p))[1]) << 8) | \
    ((u_int32_t)(((u_int8_t *)(p))[2]) << 16) | \
    ((u_int32_t)(((u_int8_t *)(p))[3]) << 24))

#define rollLeft(valueToRoll, distance) (valueToRoll << distance | valueToRoll >> (32 - distance))

#define quarterRound(a, b, c, d) \
 { \
    a += b; \
    d ^= a; \
    d = rollLeft(d, 16); \
    c += d; \
    b ^= c; \
    b = rollLeft(b, 12); \
    a += b; \
    d ^= a; \
    d = rollLeft(d, 8); \
    c += d; \
    b ^= c; \
    b = rollLeft(b, 7); \
 }

void ChaChaEncrypt(const u_int8_t *key, const u_int8_t *nonce,
                   u_int32_t *counter, u_int8_t NumRounds,
                   u_int32_t plaintextLen, u_int8_t *plaintext){

    u_int32_t state[16] = {
            0x61707865, 0x3320646e, 0x79622d32, 0x6b206574 // Constants "expa" "nd 3" "2-by" "te k"
    };

    u_int32_t original_state[16];
    u_int32_t offset = 0;

    state[4] = LE32(key);
    state[5] = LE32(key + 4);
    state[6] = LE32(key + 8);
    state[7] = LE32(key + 12);

    state[8] = LE32(key + 16);
    state[9] = LE32(key + 20);
    state[10] = LE32(key + 24);
    state[11] = LE32(key + 28);

    state[12] = *counter;

    state[13] = LE32(nonce);
    state[14] = LE32(nonce + 4);
    state[15] = LE32(nonce + 8);



    for(u_int8_t i = 0; i < 16; i++) {
        original_state[i] = state[i];
    }

    printf("%08x%08x%08x%08x\n", state[0], state[1], state[2], state[3]);
    printf("%08x%08x%08x%08x\n", state[4], state[5], state[6], state[7]);
    printf("%08x%08x%08x%08x\n", state[8], state[9], state[10], state[11]);
    printf("%08x%08x%08x%08x\n", state[12], state[13], state[14], state[15]);

    for(u_int64_t i = 0; i < NumRounds; i += 2){
        fullRound(state);
    }

    // Add the original state to the current state and reformat it in little endian format
    for(u_int8_t i = 0; i < 16; i++) {
        state[i] = state[i] + original_state[i];
        //state[i] = __bswap_32(state[i]);
    }

    // Is this defined behavior???
    u_int8_t *willThisWork = (u_int8_t*)state;

    for(u_int8_t i = 0; i < 64; i++){
        plaintext[i] = plaintext[i] ^ willThisWork[i];
        printf("%02x\n", willThisWork[i]);
    }

    printf("\n");
    printf("%08x%08x%08x%08x\n", state[0], state[1], state[2], state[3]);
    printf("%08x%08x%08x%08x\n", state[4], state[5], state[6], state[7]);
    printf("%08x%08x%08x%08x\n", state[8], state[9], state[10], state[11]);
    printf("%08x%08x%08x%08x\n", state[12], state[13], state[14], state[15]);

    // Set the state back to its original position
    for(u_int8_t i = 0; i < 16; i++) {
        state[i] = original_state[i];
    }

    // Increment the counter, both for this function and globally
    state[12] = *counter = *counter + 1;

    offset++;

}

// This function actually implements two rounds in one
// The column manipulation and the diagonal row manipulation are considered separate rounds
void fullRound(u_int32_t state[]){

    // ChaCha column rounds
    /*
      QUARTERROUND(0, 4, 8, 12)
      QUARTERROUND(1, 5, 9, 13)
      QUARTERROUND(2, 6, 10, 14)
      QUARTERROUND(3, 7, 11, 15)
     */
    quarterRound(state[0], state[4], state[8], state[12]);
    quarterRound(state[1], state[5], state[9], state[13]);
    quarterRound(state[2], state[6], state[10], state[14]);
    quarterRound(state[3], state[7], state[11], state[15]);

    // Chacha diagonal rounds
    /*
      QUARTERROUND(0, 5, 10, 15)
      QUARTERROUND(1, 6, 11, 12)
      QUARTERROUND(2, 7, 8, 13)
      QUARTERROUND(3, 4, 9, 14)
     */
    quarterRound(state[0], state[5], state[10], state[15]);
    quarterRound(state[1], state[6], state[11], state[12]);
    quarterRound(state[2], state[7], state[8], state[13]);
    quarterRound(state[3], state[4], state[9], state[14]);
}
/*
void quarterRound(u_int32_t *a, u_int32_t *b, u_int32_t *c, u_int32_t *d){

    // https://tools.ietf.org/html/rfc8439#section-2.1

    // a += b; d ^= a; d <<<= 16;
    *a += *b;
    *d ^= *a;
    *d = rollLeft(*d, 16);

    // c += d; b ^= c; b <<<= 12;
    *c += *d;
    *b ^= *c;
    *b = rollLeft(*b, 12);

    // a += b; d ^= a; d <<<= 8;
    *a += *b;
    *d ^= *a;
    *d = rollLeft(*d, 8);

    // c += d; b ^= c; b <<<= 7;
    *c += *d;
    *b ^= *c;
    *b = rollLeft(*b, 7);
}

u_int32_t rollLeft(u_int32_t valueToRoll, int distance){
    return valueToRoll << distance | valueToRoll >> (32 - distance);
}
 */
