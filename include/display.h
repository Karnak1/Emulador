#ifndef DISPLAY_H
#define DISPLAY_H

#include "chip8.h"

/* Funções de display */
void display_init(Chip8 *chip8);
void display_clear(Chip8 *chip8);
void display_draw_sprite(Chip8 *chip8, uint16_t x, uint16_t y, uint8_t height);
int display_get_pixel(Chip8 *chip8, uint16_t x, uint16_t y);
void display_set_pixel(Chip8 *chip8, uint16_t x, uint16_t y, int value);
void display_toggle_pixel(Chip8 *chip8, uint16_t x, uint16_t y);
void display_render(Chip8 *chip8);

#endif
