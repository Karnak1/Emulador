#ifndef MEMORY_H
#define MEMORY_H

#include "chip8.h"

/* Funções de memória */
void memory_init(Chip8 *chip8);
void memory_write(Chip8 *chip8, uint16_t address, uint8_t value);
uint8_t memory_read(Chip8 *chip8, uint16_t address);
uint16_t memory_read_word(Chip8 *chip8, uint16_t address);

#endif
