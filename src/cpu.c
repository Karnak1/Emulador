#include "cpu.h"
#include "memory.h"
#include "display.h"
#include "keyboard.h"
#include "timer.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void cpu_push_stack(Chip8 *chip8, uint16_t value) {
    if (chip8->stack_pointer < STACK_SIZE) {
        chip8->stack[chip8->stack_pointer++] = value;
    }
}

uint16_t cpu_pop_stack(Chip8 *chip8) {
    if (chip8->stack_pointer > 0) {
        return chip8->stack[--chip8->stack_pointer];
    }
    return 0;
}

void cpu_fetch(Chip8 *chip8) {
    chip8->opcode = memory_read_word(chip8, chip8->program_counter);
}

void cpu_decode_and_execute(Chip8 *chip8) {
    uint16_t opcode = chip8->opcode;
    uint8_t x = (opcode >> 8) & 0x0F;
    uint8_t y = (opcode >> 4) & 0x0F;
    uint8_t n = opcode & 0x0F;
    uint8_t kk = opcode & 0xFF;
    uint16_t nnn = opcode & 0x0FFF;
    
    switch (opcode & 0xF000) {
        case 0x0000:
            if (opcode == 0x00E0) {
                /* 00E0: Limpar display */
                display_clear(chip8);
            } else if (opcode == 0x00EE) {
                /* 00EE: Retornar de subrotina */
                chip8->program_counter = cpu_pop_stack(chip8);
                return;
            }
            break;
            
        case 0x1000:
            /* 1nnn: Pular para endereço nnn */
            chip8->program_counter = nnn;
            return;
            
        case 0x2000:
            /* 2nnn: Chamar subrotina em nnn */
            cpu_push_stack(chip8, chip8->program_counter);
            chip8->program_counter = nnn;
            return;
            
        case 0x3000:
            /* 3xkk: Pular próxima instrução se Vx == kk */
            if (chip8->registers[x] == kk) {
                chip8->program_counter += 2;
            }
            break;
            
        case 0x4000:
            /* 4xkk: Pular próxima instrução se Vx != kk */
            if (chip8->registers[x] != kk) {
                chip8->program_counter += 2;
            }
            break;
            
        case 0x5000:
            /* 5xy0: Pular próxima instrução se Vx == Vy */
            if (chip8->registers[x] == chip8->registers[y]) {
                chip8->program_counter += 2;
            }
            break;
            
        case 0x6000:
            /* 6xkk: Setar Vx = kk */
            chip8->registers[x] = kk;
            break;
            
        case 0x7000:
            /* 7xkk: Adicionar kk a Vx */
            chip8->registers[x] += kk;
            break;
            
        case 0x8000:
            switch (opcode & 0x000F) {
                case 0x0:
                    /* 8xy0: Setar Vx = Vy */
                    chip8->registers[x] = chip8->registers[y];
                    break;
                case 0x1:
                    /* 8xy1: Setar Vx = Vx OR Vy */
                    chip8->registers[x] |= chip8->registers[y];
                    break;
                case 0x2:
                    /* 8xy2: Setar Vx = Vx AND Vy */
                    chip8->registers[x] &= chip8->registers[y];
                    break;
                case 0x3:
                    /* 8xy3: Setar Vx = Vx XOR Vy */
                    chip8->registers[x] ^= chip8->registers[y];
                    break;
                case 0x4:
                    /* 8xy4: Adicionar Vy a Vx, setar VF = carry */
                    if ((uint16_t)chip8->registers[x] + chip8->registers[y] > 255) {
                        chip8->registers[0xF] = 1;
                    } else {
                        chip8->registers[0xF] = 0;
                    }
                    chip8->registers[x] += chip8->registers[y];
                    break;
                case 0x5:
                    /* 8xy5: Subtrair Vy de Vx, setar VF = NOT borrow */
                    if (chip8->registers[x] > chip8->registers[y]) {
                        chip8->registers[0xF] = 1;
                    } else {
                        chip8->registers[0xF] = 0;
                    }
                    chip8->registers[x] -= chip8->registers[y];
                    break;
                case 0x6:
                    /* 8xy6: Deslocar Vx para direita, VF = LSB de Vx */
                    chip8->registers[0xF] = chip8->registers[x] & 1;
                    chip8->registers[x] >>= 1;
                    break;
                case 0x7:
                    /* 8xy7: Setar Vx = Vy - Vx, VF = NOT borrow */
                    if (chip8->registers[y] > chip8->registers[x]) {
                        chip8->registers[0xF] = 1;
                    } else {
                        chip8->registers[0xF] = 0;
                    }
                    chip8->registers[x] = chip8->registers[y] - chip8->registers[x];
                    break;
                case 0xE:
                    /* 8xyE: Deslocar Vx para esquerda, VF = MSB de Vx */
                    chip8->registers[0xF] = (chip8->registers[x] >> 7) & 1;
                    chip8->registers[x] <<= 1;
                    break;
            }
            break;
            
        case 0x9000:
            /* 9xy0: Pular próxima instrução se Vx != Vy */
            if (chip8->registers[x] != chip8->registers[y]) {
                chip8->program_counter += 2;
            }
            break;
            
        case 0xA000:
            /* Annn: Setar I = nnn */
            chip8->index_register = nnn;
            break;
            
        case 0xB000:
            /* Bnnn: Pular para nnn + V0 */
            chip8->program_counter = nnn + chip8->registers[0];
            return;
            
        case 0xC000:
            /* Cxkk: Setar Vx = número aleatório AND kk */
            chip8->registers[x] = (rand() % 256) & kk;
            break;
            
        case 0xD000: {
            /* Dxyn: Desenhar sprite em (Vx, Vy) com altura n */
            uint16_t x_pos = chip8->registers[x] % DISPLAY_WIDTH;
            uint16_t y_pos = chip8->registers[y] % DISPLAY_HEIGHT;
            chip8->registers[0xF] = 0;
            
            for (int row = 0; row < n; row++) {
                uint8_t sprite_byte = memory_read(chip8, chip8->index_register + row);
                
                for (int col = 0; col < 8; col++) {
                    int bit = (sprite_byte >> (7 - col)) & 1;
                    int current_x = (x_pos + col) % DISPLAY_WIDTH;
                    int current_y = (y_pos + row) % DISPLAY_HEIGHT;
                    
                    if (bit) {
                        int pixel = display_get_pixel(chip8, current_x, current_y);
                        if (pixel) {
                            chip8->registers[0xF] = 1;
                        }
                        display_toggle_pixel(chip8, current_x, current_y);
                    }
                }
            }
            break;
        }
            
        case 0xE000:
            switch (opcode & 0xFF) {
                case 0x9E:
                    /* Ex9E: Pular próxima instrução se tecla Vx está pressionada */
                    if (keyboard_is_pressed(chip8, chip8->registers[x])) {
                        chip8->program_counter += 2;
                    }
                    break;
                case 0xA1:
                    /* ExA1: Pular próxima instrução se tecla Vx NÃO está pressionada */
                    if (!keyboard_is_pressed(chip8, chip8->registers[x])) {
                        chip8->program_counter += 2;
                    }
                    break;
            }
            break;
            
        case 0xF000:
            switch (opcode & 0xFF) {
                case 0x07:
                    /* Fx07: Setar Vx = delay timer */
                    chip8->registers[x] = timer_get_delay(chip8);
                    break;
                case 0x0A: {
                    /* Fx0A: Aguardar pressionamento de tecla, armazenar em Vx */
                    int key_pressed = 0;
                    for (int i = 0; i < 16; i++) {
                        if (keyboard_is_pressed(chip8, i)) {
                            chip8->registers[x] = i;
                            key_pressed = 1;
                            break;
                        }
                    }
                    if (!key_pressed) {
                        chip8->program_counter -= 2;
                    }
                    break;
                }
                case 0x15:
                    /* Fx15: Setar delay timer = Vx */
                    timer_set_delay(chip8, chip8->registers[x]);
                    break;
                case 0x18:
                    /* Fx18: Setar sound timer = Vx */
                    timer_set_sound(chip8, chip8->registers[x]);
                    break;
                case 0x1E:
                    /* Fx1E: Adicionar Vx a I */
                    chip8->index_register += chip8->registers[x];
                    break;
                case 0x29:
                    /* Fx29: Setar I = localização do sprite para digit Vx */
                    chip8->index_register = 0x50 + (chip8->registers[x] * 5);
                    break;
                case 0x33: {
                    /* Fx33: Armazenar representação BCD de Vx em I, I+1, I+2 */
                    uint8_t vx = chip8->registers[x];
                    memory_write(chip8, chip8->index_register, vx / 100);
                    memory_write(chip8, chip8->index_register + 1, (vx / 10) % 10);
                    memory_write(chip8, chip8->index_register + 2, vx % 10);
                    break;
                }
                case 0x55:
                    /* Fx55: Armazenar V0 a Vx em memória começando em I */
                    for (int i = 0; i <= x; i++) {
                        memory_write(chip8, chip8->index_register + i, chip8->registers[i]);
                    }
                    break;
                case 0x65:
                    /* Fx65: Carregar V0 a Vx de memória começando em I */
                    for (int i = 0; i <= x; i++) {
                        chip8->registers[i] = memory_read(chip8, chip8->index_register + i);
                    }
                    break;
            }
            break;
            
        default:
            fprintf(stderr, "Opcode desconhecido: 0x%X\n", opcode);
            break;
    }
    
    chip8->program_counter += 2;
}

void cpu_cycle(Chip8 *chip8) {
    cpu_fetch(chip8);
    cpu_decode_and_execute(chip8);
    timer_tick(chip8);
}
