#ifndef CPU_H
#define CPU_H

#include "chip8.h"

/* Funções da CPU */
void cpu_fetch(Chip8 *chip8);
void cpu_decode_and_execute(Chip8 *chip8);
void cpu_cycle(Chip8 *chip8);

/* Funções auxiliares para instruções */
void cpu_push_stack(Chip8 *chip8, uint16_t value);
uint16_t cpu_pop_stack(Chip8 *chip8);

#endif
