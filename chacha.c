//
// Created by cole on 5/2/21.
//

#include "chacha.h"

/*#define quarterRound(a, b, c, d) \
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
 }*/

// This function actually implements two rounds in one
// The column manipulation and the diagonal row manipulation are considered seperate rounds
void fullRound(u_int32_t state[]){

    // ChaCha column rounds
    /*
      QUARTERROUND(0, 4, 8, 12)
      QUARTERROUND(1, 5, 9, 13)
      QUARTERROUND(2, 6, 10, 14)
      QUARTERROUND(3, 7, 11, 15)
     */
    quarterRound(&state[0], &state[4], &state[8], &state[12]);
    quarterRound(&state[1], &state[5], &state[9], &state[13]);
    quarterRound(&state[2], &state[6], &state[10], &state[14]);
    quarterRound(&state[3], &state[7], &state[11], &state[15]);

    // Chacha diagonal rounds
    /*
      QUARTERROUND(0, 5, 10, 15)
      QUARTERROUND(1, 6, 11, 12)
      QUARTERROUND(2, 7, 8, 13)
      QUARTERROUND(3, 4, 9, 14)
     */
    quarterRound(&state[0], &state[5], &state[10], &state[15]);
    quarterRound(&state[1], &state[6], &state[11], &state[12]);
    quarterRound(&state[2], &state[7], &state[8], &state[13]);
    quarterRound(&state[3], &state[4], &state[9], &state[14]);
}

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