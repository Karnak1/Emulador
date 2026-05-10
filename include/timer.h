#ifndef TIMER_H
#define TIMER_H

#include "chip8.h"

/* Funções de timer */
void timer_init(Chip8 *chip8);
void timer_tick(Chip8 *chip8);
void timer_set_delay(Chip8 *chip8, uint8_t value);
void timer_set_sound(Chip8 *chip8, uint8_t value);
uint8_t timer_get_delay(Chip8 *chip8);
uint8_t timer_get_sound(Chip8 *chip8);

#endif
