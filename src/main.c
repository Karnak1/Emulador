#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "include/chip8.h"
#include "include/memory.h"
#include "include/cpu.h"
#include "include/display.h"
#include "include/keyboard.h"
#include "include/timer.h"
#include "include/rom_loader.h"

void chip8_init(Chip8 *chip8) {
    memset(chip8, 0, sizeof(Chip8));
    
    /* Inicializar componentes */
    memory_init(chip8);
    display_init(chip8);
    keyboard_init(chip8);
    timer_init(chip8);
    
    /* Configurar program counter para início da ROM */
    chip8->program_counter = ROM_START_ADDRESS;
    chip8->running = 1;
    
    srand(time(NULL));
}

void print_display(Chip8 *chip8) {
    printf("\n");
    for (int y = 0; y < DISPLAY_HEIGHT; y++) {
        for (int x = 0; x < DISPLAY_WIDTH; x++) {
            printf("%c", chip8->display[y * DISPLAY_WIDTH + x] ? '#' : ' ');
        }
        printf("\n");
    }
    printf("\n");
}

void print_cpu_state(Chip8 *chip8) {
    printf("=== Estado da CPU ===\n");
    printf("PC: 0x%04X | Opcode: 0x%04X\n", chip8->program_counter, chip8->opcode);
    printf("I: 0x%04X | SP: %d\n", chip8->index_register, chip8->stack_pointer);
    printf("Registradores:\n");
    for (int i = 0; i < 16; i++) {
        printf("V%X: 0x%02X ", i, chip8->registers[i]);
        if ((i + 1) % 4 == 0) printf("\n");
    }
    printf("Timers - Delay: %d, Sound: %d\n", chip8->delay_timer, chip8->sound_timer);
    printf("\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: %s <caminho_da_rom> [num_ciclos]\n", argv[0]);
        printf("\nExemplo: %s roms/pong.ch8 1000\n", argv[0]);
        return 1;
    }
    
    const char *rom_path = argv[1];
    int num_cycles = (argc > 2) ? atoi(argv[2]) : 100;
    
    Chip8 chip8;
    chip8_init(&chip8);
    
    if (!rom_load(&chip8, rom_path)) {
        fprintf(stderr, "Falha ao carregar ROM\n");
        return 1;
    }
    
    printf("Executando emulador CHIP-8\n");
    printf("ROM: %s\n", rom_path);
    printf("Ciclos: %d\n\n", num_cycles);
    
    /* Executar ciclos */
    for (int i = 0; i < num_cycles && chip8.running; i++) {
        printf("--- Ciclo %d ---\n", i + 1);
        print_cpu_state(&chip8);
        
        cpu_cycle(&chip8);
        
        /* Renderizar display a cada ciclo */
        if (i % 10 == 0) {
            printf("Display:\n");
            print_display(&chip8);
        }
    }
    
    printf("Emulação finalizada\n");
    return 0;
}
