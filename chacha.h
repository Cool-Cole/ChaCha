#include <stdlib.h>
#include <error.h>

#ifndef CHACHA_CHACHAQUARTERROUND_H
#define CHACHA_CHACHAQUARTERROUND_H

/*
 * The key must be 32 bytes (or 256 bits)
 * The nonce must be 12 bytes (or 96 bits)
 * When this function is first called the counter var must be
 */
void ChaChaEncrypt(const u_int8_t *key, const u_int8_t *nonce,
                   u_int32_t *counter, u_int8_t NumRounds,
                   u_int32_t plaintextLen, void *plaintext);

void fullRound(u_int32_t state[]);

void quarterRound(u_int32_t *a, u_int32_t *b, u_int32_t *c, u_int32_t *d);

u_int32_t rollLeft(u_int32_t valueToRoll, int distance);

#endif //CHACHA_CHACHAQUARTERROUND_H
