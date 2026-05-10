/*
 * EXEMPLO: Integração com SDL2 para renderização gráfica
 * 
 * Este arquivo mostra como expandir o emulador com visualização real
 * 
 * Compilação com SDL2:
 * gcc -Wall -std=c99 -I. -I/usr/include/SDL2 src/*.c $(sdl2-config --cflags --libs) -o chip8_emulator
 */

#ifdef USE_SDL2

#include <SDL2/SDL.h>
#include "include/chip8.h"
#include "include/display.h"

#define PIXEL_SIZE 10  // Tamanho de cada pixel em pixels da tela

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
} DisplayContext;

static DisplayContext display_ctx = {NULL, NULL};

int display_init_graphics(void) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Erro ao inicializar SDL: %s\n", SDL_GetError());
        return 0;
    }
    
    display_ctx.window = SDL_CreateWindow(
        "CHIP-8 Emulator",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        DISPLAY_WIDTH * PIXEL_SIZE,
        DISPLAY_HEIGHT * PIXEL_SIZE,
        SDL_WINDOW_SHOWN
    );
    
    if (!display_ctx.window) {
        printf("Erro ao criar janela: %s\n", SDL_GetError());
        return 0;
    }
    
    display_ctx.renderer = SDL_CreateRenderer(
        display_ctx.window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );
    
    if (!display_ctx.renderer) {
        printf("Erro ao criar renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(display_ctx.window);
        return 0;
    }
    
    return 1;
}

void display_render_sdl2(Chip8 *chip8) {
    if (!display_ctx.renderer) return;
    
    /* Fundo preto */
    SDL_SetRenderDrawColor(display_ctx.renderer, 0, 0, 0, 255);
    SDL_RenderClear(display_ctx.renderer);
    
    /* Desenhar pixels brancos */
    SDL_SetRenderDrawColor(display_ctx.renderer, 255, 255, 255, 255);
    
    for (int y = 0; y < DISPLAY_HEIGHT; y++) {
        for (int x = 0; x < DISPLAY_WIDTH; x++) {
            if (chip8->display[y * DISPLAY_WIDTH + x]) {
                SDL_Rect rect = {
                    x * PIXEL_SIZE,
                    y * PIXEL_SIZE,
                    PIXEL_SIZE,
                    PIXEL_SIZE
                };
                SDL_RenderFillRect(display_ctx.renderer, &rect);
            }
        }
    }
    
    SDL_RenderPresent(display_ctx.renderer);
}

void display_cleanup(void) {
    if (display_ctx.renderer) {
        SDL_DestroyRenderer(display_ctx.renderer);
    }
    if (display_ctx.window) {
        SDL_DestroyWindow(display_ctx.window);
    }
    SDL_Quit();
}

/*
 * EXEMPLO DE LOOP PRINCIPAL COM SDL2:
 * 
 * int main(int argc, char *argv[]) {
 *     Chip8 chip8;
 *     chip8_init(&chip8);
 *     
 *     if (!rom_load(&chip8, argv[1])) return 1;
 *     if (!display_init_graphics()) return 1;
 *     
 *     SDL_Event event;
 *     int running = 1;
 *     
 *     while (running && chip8.running) {
 *         // Processar eventos
 *         while (SDL_PollEvent(&event)) {
 *             if (event.type == SDL_QUIT) running = 0;
 *             else if (event.type == SDL_KEYDOWN) {
 *                 int key = map_sdl_key_to_chip8(event.key.keysym.sym);
 *                 if (key >= 0) keyboard_press(&chip8, key);
 *             }
 *             else if (event.type == SDL_KEYUP) {
 *                 int key = map_sdl_key_to_chip8(event.key.keysym.sym);
 *                 if (key >= 0) keyboard_release(&chip8, key);
 *             }
 *         }
 *         
 *         // Executar CPU (múltiplos ciclos por frame)
 *         for (int i = 0; i < 10; i++) {
 *             cpu_cycle(&chip8);
 *         }
 *         
 *         // Renderizar
 *         display_render_sdl2(&chip8);
 *     }
 *     
 *     display_cleanup();
 *     return 0;
 * }
 */

#endif // USE_SDL2
