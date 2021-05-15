#ifndef CHACHA_H
#define CHACHA_H

//C++ guard
#ifdef __cplusplus
extern "C" {
#endif

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
 * When this function is first called the counter must be 1 unless you want to reinitialize the state to a certain point in the encryption process
 * For ChaCha 20 make sure that NumRounds == 20
 * For ChaCha 12 make sure that NumRounds == 12
 * For ChaCha 8 make sure that NumRounds == 8
 */
void ChaChaInitialize(chachastate *cipherInfo, const uint8_t *key, const uint8_t *nonce,
                      uint32_t *counter, uint8_t NumRounds);

/*
 * This function takes an initialized ChaCha state, a plaintext and the length of the plaintext.
 * The plaintext is encrypted in place.
 */
void ChaChaEncrypt(chachastate *cipherInfo, uint32_t plainTextLen, uint8_t *plainText);

/*
 * This function takes an initialized ChaCha state, a ciphertext and the length of the ciphertext.
 * The plaintext is decrypted in place.
 */
void ChaChaDecrypt(chachastate *cipherInfo, uint32_t plainTextLen, uint8_t *cipherText);

// Don't use this, may be replaced with function definition in future version.
void fullRound(uint32_t state[]);

//C++ guard
#ifdef __cplusplus
}
#endif


#endif //CHACHA_H
