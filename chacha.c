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

    uint32_t *original_state = cipherInfo->original_sate;
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

    // Copy over the current state to the array that holds the temporary state
    for(uint8_t i = 0; i < 16; i++) {
        original_state[i] = word[i];
    }

}

void ChaChaEncrypt(chachastate *cipherInfo, uint32_t plaintextLen, uint8_t *plaintext){

    uint32_t *state = cipherInfo->state;
    uint32_t *original_state = cipherInfo->original_sate;
    uint8_t NumRounds = cipherInfo->NumRounds;

    uint32_t position = 0;

    // This loop encrypts the entire len of the plaintext
    while(plaintextLen > 0){

        // Manipulate the working state
        for(uint64_t i = 0; i < NumRounds; i += 2){
            fullRound(state);
        }

        // Add the original state to the current state and reformat it in little endian format
        for(uint8_t i = 0; i < 16; i++) {
            state[i] = state[i] + original_state[i];
        }

        // Apparently, you can turn an array of 4 byte words into 1 byte words!
        // Cool!
        uint8_t *stateByteArray = (uint8_t*)state;

        if(plaintextLen < 64){
            // XOR the contents of the chacha state with the plaintext

            printf("0x%08x 0x%08x 0x%08x 0x%08x\n", state[0], state[1], state[2], state[3]);
            printf("0x%08x 0x%08x 0x%08x 0x%08x\n", state[4], state[5], state[6], state[7]);
            printf("0x%08x 0x%08x 0x%08x 0x%08x\n", state[8], state[9], state[10], state[11]);
            printf("0x%08x 0x%08x 0x%08x 0x%08x\n", state[12], state[13], state[14], state[15]);

            printf("\n");

            int i = 0;
            while(plaintextLen > 0){
                plaintext[position] = plaintext[position] ^ stateByteArray[i];
                //plaintext[position] = stateByteArray[i];
                position++;
                i++;
                plaintextLen--;
            }

        } else {
            // XOR the contents of the chacha state with the plaintext
            for(uint8_t i = 0; i < 64; i++) {
                plaintext[position] = plaintext[position] ^ stateByteArray[i];
                //plaintext[position] = stateByteArray[i];
                position++;
            }

            plaintextLen = plaintextLen - 64;

        }

        // Set the state back to its original position
        for(uint8_t i = 0; i < 16; i++) {
            state[i] = original_state[i];
        }

        // Increment the counter, both for this function and globally
        state[12] = state[12] + 1;
        original_state[12] = state[12];


    }

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
