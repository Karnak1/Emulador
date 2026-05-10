#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "chip8.h"

/* Funções de teclado */
void keyboard_init(Chip8 *chip8);
void keyboard_press(Chip8 *chip8, uint8_t key);
void keyboard_release(Chip8 *chip8, uint8_t key);
int keyboard_is_pressed(Chip8 *chip8, uint8_t key);

#endif
