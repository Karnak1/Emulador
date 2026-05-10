<<<<<<< HEAD
# Emulador CHIP-8 em C e Python

Um emulador modular e didático da máquina virtual **CHIP-8**, escrito em C puro.

## 📋 O que é CHIP-8?

CHIP-8 é uma máquina virtual simples criada em 1977, originalmente usada para desenvolver jogos em computadores antigos como o COSMAC VIP. É perfeita para aprender sobre emulação.

**Características:**
- 16 registradores de 8 bits (V0-VF)
- 4KB de memória
- Display monitorado 64x32 pixels
- 16 teclas hexadecimais (0-F)
- 35 instruções de 16 bits

## 🗂️ Estrutura do Projeto

```
emulador/
├── include/              # Headers (.h)
│   ├── chip8.h          # Estruturas principais
│   ├── cpu.h            # CPU (fetch, decode, execute)
│   ├── memory.h         # Gerenciamento de memória
│   ├── display.h        # Sistema de vídeo
│   ├── keyboard.h       # Input de teclado
│   ├── timer.h          # Timers (delay, sound)
│   └── rom_loader.h     # Carregador de ROMs
├── src/                  # Implementações (.c)
│   ├── cpu.c
│   ├── memory.c
│   ├── display.c
│   ├── keyboard.c
│   ├── timer.c
│   ├── rom_loader.c
│   └── main.c           # Loop principal
├── roms/                # Pasta para ROMs CHIP-8
├── obj/                 # Arquivos objeto (gerado)
├── Makefile             # Build system
└── README.md           # Este arquivo
```

## 🛠️ Compilação

### Pré-requisitos
- GCC (ou outro compilador C)
- Make

### Compilar
```bash
make
```

### Limpar
```bash
make clean
```

## 🎮 Uso

### Executar com uma ROM
```bash
./chip8_emulator roms/seu_jogo.ch8
```

### Executar com limite de ciclos
```bash
./chip8_emulator roms/seu_jogo.ch8 1000
```

## 📦 Módulos Principais

### `chip8.h`
Define a estrutura principal `Chip8` que contém:
- Memória (4KB)
- Registradores (16)
- Stack (para chamadas de subrotina)
- Display (64x32)
- Teclado e Timers

### `cpu.c`
Implementa o ciclo de execução:
1. **Fetch**: Busca opcode da memória
2. **Decode**: Interpreta o opcode
3. **Execute**: Executa a instrução

Todas as 35 instruções CHIP-8 são implementadas.

### `memory.c`
- Inicialização com fontset (0-F)
- Leitura/escrita de bytes
- Leitura de palavras (16 bits)

### `display.c`
- Buffer de pixels 64x32
- Funções para renderizar sprites
- Clear display

### `keyboard.c`
- Mapear 16 teclas hexadecimais
- Detectar pressionamento/liberação

### `timer.c`
- Timers de delay e som
- Decrementam a 60Hz

### `rom_loader.c`
- Carregar ROM em memória
- Validações de tamanho

## 📚 Instruções CHIP-8 Implementadas

| Categoria | Instruções |
|-----------|-----------|
| Flow | 1nnn, 00E0, 00EE, 2nnn |
| Conditional | 3xkk, 4xkk, 5xy0, 9xy0 |
| Constants | 6xkk, 7xkk |
| Register | 8xy0-8xyE |
| Memory | Annn, Fx55, Fx65 |
| Display | Dxyn |
| Keyboard | Ex9E, ExA1, Fx0A |
| Timers | Fx07, Fx15, Fx18 |
| Sound | Fx18 |
| Misc | Cxkk, Bnnn, Fx1E, Fx29, Fx33 |

## 🔧 Como Expandir

### Adicionar Renderização Gráfica
O código está preparado para integrar SDL2 ou outra biblioteca:

```c
// Em display.c, implementar:
void display_render(Chip8 *chip8) {
    // Usar SDL2 para desenhar pixels
}
```

### Adicionar Som
O timer de som já está implementado. Integrar audio:

```c
// Em audio.c (novo módulo)
void audio_beep(uint8_t duration);
```

### Aumentar Performance
Adicionar dinâmica de clock:
- Executar ~500-1000 ciclos/segundo
- Usar `usleep()` para síncrono timing

## 📝 Mapeo de Teclado

CHIP-8 usa 16 teclas hexadecimais (0-F). Mapeamento sugerido:

```
CHIP-8:     Teclado:
1 2 3 C     1 2 3 4
4 5 6 D  →  Q W E R
7 8 9 E     A S D F
A 0 B F     Z X C V
```

## 🎯 Próximos Passos

1. **Integrar SDL2** para renderização gráfica
2. **Adicionar áudio** com sintetizador simples
3. **Melhorar timing** para velocidade consistente
4. **Debugger visual** com breakpoints
5. **Mais testes** com diferentes ROMs

## 📖 Recursos

- [CHIP-8 Specification](http://devernay.free.fr/hacks/chip8/C8TECH10.HTM)
- [CHIP-8 Emulator Guide](https://tobiasvl.github.io/blog/write-a-chip-8-emulator/)
- [Test ROMs](https://github.com/corax89/chip8-test-rom)

## 📄 Licença

Este projeto é de código aberto para fins educacionais.

---

**Desenvolvido em 2026** - Emulador didático para aprender sobre máquinas virtuais e emulação.
=======
# Emulador
>>>>>>> feb3c3f762e5155b844ad0090e1ff5613ef8a621
