#include "keyboard.h"

void keyboard_init(Chip8 *chip8) {
    for (int i = 0; i < 16; i++) {
        chip8->keys[i] = 0;
    }
}

void keyboard_press(Chip8 *chip8, uint8_t key) {
    if (key < 16) {
        chip8->keys[key] = 1;
    }
}

void keyboard_release(Chip8 *chip8, uint8_t key) {
    if (key < 16) {
        chip8->keys[key] = 0;
    }
}

int keyboard_is_pressed(Chip8 *chip8, uint8_t key) {
    if (key < 16) {
        return chip8->keys[key];
    }
    return 0;
}
