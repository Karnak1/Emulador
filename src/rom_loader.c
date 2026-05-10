#include "rom_loader.h"
#include <stdio.h>
#include <stdlib.h>

int rom_load(Chip8 *chip8, const char *filepath) {
    FILE *rom_file = fopen(filepath, "rb");
    if (!rom_file) {
        fprintf(stderr, "Erro ao abrir ROM: %s\n", filepath);
        return 0;
    }
    
    /* Buscar tamanho do arquivo */
    fseek(rom_file, 0, SEEK_END);
    long rom_size = ftell(rom_file);
    fseek(rom_file, 0, SEEK_SET);
    
    /* Verificar se o tamanho é válido */
    if (rom_size > MEMORY_SIZE - ROM_START_ADDRESS) {
        fprintf(stderr, "ROM muito grande: %ld bytes\n", rom_size);
        fclose(rom_file);
        return 0;
    }
    
    /* Carregar ROM na memória */
    size_t bytes_read = fread(&chip8->memory[ROM_START_ADDRESS], 1, rom_size, rom_file);
    fclose(rom_file);
    
    if (bytes_read != rom_size) {
        fprintf(stderr, "Erro ao ler ROM\n");
        return 0;
    }
    
    printf("ROM carregada com sucesso: %ld bytes\n", rom_size);
    return 1;
}
