#ifndef CHACHA_CHACHAQUARTERROUND_H
#define CHACHA_CHACHAQUARTERROUND_H

#include <stdint.h>

typedef struct {
    uint8_t NumRounds;
    uint8_t keyStreamPosition;
    uint32_t state[16];
    uint32_t original_sate[16];
} chachastate;


/*
 * The key must be 32 bytes (or 256 bits)
 * The nonce must be 12 bytes (or 96 bits)
 * When this function is first called the counter must be 1 unless you want to reinitialize the state at certian points in the encryption process
 */
void ChaChaInitialize(chachastate *cipherInfo, const uint8_t *key, const uint8_t *nonce,
                      uint32_t *counter, uint8_t NumRounds);

/*
 * This function takes an initalized ChaCha state, a plaintext and the length of the plaintext.
 * The plaintext is encrypted in place.
 */
void ChaChaEncrypt(chachastate *cipherInfo, uint32_t plaintextLen, uint8_t *plaintext);

// Don't use this, may be replaced with function definition in future version.
void fullRound(uint32_t state[]);

#endif //CHACHA_CHACHAQUARTERROUND_H
