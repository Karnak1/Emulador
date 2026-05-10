#ifndef CHIP8_H
#define CHIP8_H

#include <stdint.h>

/* Constantes CHIP-8 */
#define MEMORY_SIZE 4096
#define ROM_START_ADDRESS 0x200
#define DISPLAY_WIDTH 64
#define DISPLAY_HEIGHT 32
#define NUM_REGISTERS 16
#define STACK_SIZE 16

/* Estrutura principal da VM CHIP-8 */
typedef struct {
    /* Memória */
    uint8_t memory[MEMORY_SIZE];
    
    /* Registradores */
    uint8_t registers[NUM_REGISTERS];  /* V0-VF */
    uint16_t index_register;           /* I */
    uint16_t program_counter;          /* PC */
    uint16_t stack[STACK_SIZE];        /* Stack */
    uint8_t stack_pointer;             /* SP */
    
    /* Display */
    uint8_t display[DISPLAY_WIDTH * DISPLAY_HEIGHT];
    
    /* Timers */
    uint8_t delay_timer;
    uint8_t sound_timer;
    
    /* Teclado */
    uint8_t keys[16];
    
    /* Opcode atual */
    uint16_t opcode;
    
    /* Flag para parar emulação */
    int running;
} Chip8;

#endif
