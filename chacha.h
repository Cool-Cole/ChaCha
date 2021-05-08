#ifndef CHACHA_CHACHAQUARTERROUND_H
#define CHACHA_CHACHAQUARTERROUND_H

#include <stdint.h>

typedef struct {
    uint8_t NumRounds;
    uint32_t state[16];
    uint32_t original_sate[16];
} chachastate;

/*
 * The key must be 32 bytes (or 256 bits)
 * The nonce must be 12 bytes (or 96 bits)
 * When this function is first called the counter var must be
 */

void ChaChaInitialize(chachastate *cipherInfo, const uint8_t *key, const uint8_t *nonce,
                      uint32_t *counter, uint8_t NumRounds);

void ChaChaEncrypt(chachastate *cipherInfo, uint32_t plaintextLen, uint8_t *plaintext);

void fullRound(uint32_t state[]);

#endif //CHACHA_CHACHAQUARTERROUND_H
