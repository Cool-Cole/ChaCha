//
// Created by cole on 5/2/21.
//
#include <stdlib.h>

#ifndef CHACHA_CHACHAQUARTERROUND_H
#define CHACHA_CHACHAQUARTERROUND_H

void fullRound(u_int32_t state[]);

void quarterRound(u_int32_t *a, u_int32_t *b, u_int32_t *c, u_int32_t *d);

u_int32_t rollLeft(u_int32_t valueToRoll, int distance);

#endif //CHACHA_CHACHAQUARTERROUND_H
