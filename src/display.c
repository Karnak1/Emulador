#include "display.h"
#include <string.h>

void display_init(Chip8 *chip8) {
    memset(chip8->display, 0, DISPLAY_WIDTH * DISPLAY_HEIGHT);
}

void display_clear(Chip8 *chip8) {
    memset(chip8->display, 0, DISPLAY_WIDTH * DISPLAY_HEIGHT);
}

int display_get_pixel(Chip8 *chip8, uint16_t x, uint16_t y) {
    if (x >= DISPLAY_WIDTH || y >= DISPLAY_HEIGHT) {
        return 0;
    }
    return chip8->display[y * DISPLAY_WIDTH + x];
}

void display_set_pixel(Chip8 *chip8, uint16_t x, uint16_t y, int value) {
    if (x >= DISPLAY_WIDTH || y >= DISPLAY_HEIGHT) {
        return;
    }
    chip8->display[y * DISPLAY_WIDTH + x] = value ? 1 : 0;
}

void display_toggle_pixel(Chip8 *chip8, uint16_t x, uint16_t y) {
    if (x >= DISPLAY_WIDTH || y >= DISPLAY_HEIGHT) {
        return;
    }
    x %= DISPLAY_WIDTH;
    y %= DISPLAY_HEIGHT;
    chip8->display[y * DISPLAY_WIDTH + x] ^= 1;
}

void display_draw_sprite(Chip8 *chip8, uint16_t x, uint16_t y, uint8_t height) {
    /* Função para desenhar sprite (será usada pela instrução DXYN) */
    /* Implementação será feita em cpu.c */
}

void display_render(Chip8 *chip8) {
    /* Função para renderizar o display na tela */
    /* Será implementada com SDL2 ou biblioteca gráfica similar */
    /* Por enquanto, apenas stub */
}
