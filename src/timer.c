#include "timer.h"

void timer_init(Chip8 *chip8) {
    chip8->delay_timer = 0;
    chip8->sound_timer = 0;
}

void timer_tick(Chip8 *chip8) {
    if (chip8->delay_timer > 0) {
        chip8->delay_timer--;
    }
    if (chip8->sound_timer > 0) {
        chip8->sound_timer--;
    }
}

void timer_set_delay(Chip8 *chip8, uint8_t value) {
    chip8->delay_timer = value;
}

void timer_set_sound(Chip8 *chip8, uint8_t value) {
    chip8->sound_timer = value;
}

uint8_t timer_get_delay(Chip8 *chip8) {
    return chip8->delay_timer;
}

uint8_t timer_get_sound(Chip8 *chip8) {
    return chip8->sound_timer;
}
