#include "chacha.h"
#include <stdio.h>

#define LE32(p) ( \
    ((uint32_t)(((uint8_t *)(p))[0]) << 0) | \
    ((uint32_t)(((uint8_t *)(p))[1]) << 8) | \
    ((uint32_t)(((uint8_t *)(p))[2]) << 16) | \
    ((uint32_t)(((uint8_t *)(p))[3]) << 24))

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

void ChaChaInitialize(chachastate *cipherInfo, const uint8_t *key, const uint8_t *nonce,
                      uint32_t *counter, uint8_t NumRounds){

    uint32_t *word = cipherInfo->state;

    cipherInfo->NumRounds = NumRounds;

    // The constant is added to the state
    word[0] = 0x61707865;
    word[1] = 0x3320646e;
    word[2] = 0x79622d32;
    word[3] = 0x6b206574;

    // 256 bit key is added to the state
    word[4] = LE32(key);
    word[5] = LE32(key + 4);
    word[6] = LE32(key + 8);
    word[7] = LE32(key + 12);
    word[8] = LE32(key + 16);
    word[9] = LE32(key + 20);
    word[10] = LE32(key + 24);
    word[11] = LE32(key + 28);

    // The counter is added to the state
    word[12] = *counter;

    // The nonce is added to the state
    word[13] = LE32(nonce);
    word[14] = LE32(nonce + 4);
    word[15] = LE32(nonce + 8);

}

void ChaChaEncrypt(chachastate *cipherInfo, uint32_t *plaintextLen, uint8_t *plaintext){

    uint32_t *state = cipherInfo->state;
    uint32_t *original_state = cipherInfo->original_sate;
    uint8_t *NumRounds = cipherInfo->NumRounds;

    // Copy over the current state to the array that holds the temporary state
    for(uint8_t i = 0; i < 16; i++) {
        original_state[i] = state[i];
    }

    printf("%08x%08x%08x%08x\n", state[0], state[1], state[2], state[3]);
    printf("%08x%08x%08x%08x\n", state[4], state[5], state[6], state[7]);
    printf("%08x%08x%08x%08x\n", state[8], state[9], state[10], state[11]);
    printf("%08x%08x%08x%08x\n", state[12], state[13], state[14], state[15]);

    for(uint64_t i = 0; i < NumRounds; i += 2){
        fullRound(state);
    }

    // Add the original state to the current state and reformat it in little endian format
    for(uint8_t i = 0; i < 16; i++) {
        state[i] = state[i] + original_state[i];
    }

    // Is this defined behavior???
    uint8_t *stateByteArray = (uint8_t*)state;

    // XOR the contents of the chacha state with the plaintext
    for(uint8_t i = 0; i < 64; i++){
        plaintext[i] = plaintext[i] ^ stateByteArray[i];
        printf("%02x\n", stateByteArray[i]);
    }

    printf("\n");
    printf("%08x%08x%08x%08x\n", state[0], state[1], state[2], state[3]);
    printf("%08x%08x%08x%08x\n", state[4], state[5], state[6], state[7]);
    printf("%08x%08x%08x%08x\n", state[8], state[9], state[10], state[11]);
    printf("%08x%08x%08x%08x\n", state[12], state[13], state[14], state[15]);

    // Set the state back to its original position
    for(uint8_t i = 0; i < 16; i++) {
        state[i] = original_state[i];
    }

    // Increment the counter, both for this function and globally
    state[12] = state[12] + 1;

}

// This function actually implements two rounds in one
// The column manipulation and the diagonal row manipulation are considered separate rounds
void fullRound(uint32_t state[]){

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
void quarterRound(uint32_t *a, uint32_t *b, uint32_t *c, uint32_t *d){

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

uint32_t rollLeft(uint32_t valueToRoll, int distance){
    return valueToRoll << distance | valueToRoll >> (32 - distance);
}
 */
