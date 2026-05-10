#ifndef ROM_LOADER_H
#define ROM_LOADER_H

#include "chip8.h"

/* Funções de carregamento de ROM */
int rom_load(Chip8 *chip8, const char *filepath);

#endif
