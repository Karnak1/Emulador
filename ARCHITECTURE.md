# 🏗️ Arquitetura do Emulador CHIP-8

## Visão Geral

```
┌─────────────────────────────────────────┐
│     Loop Principal (main.c)             │
│  ┌───────────────────────────────────┐  │
│  │ 1. Buscar opcode (Fetch)          │  │
│  │ 2. Decodificar (Decode)           │  │
│  │ 3. Executar (Execute)             │  │
│  │ 4. Atualizar timers               │  │
│  └───────────────────────────────────┘  │
└─────────────────────────────────────────┘
          │
    ┌─────┴─────┬──────────┬─────────┐
    ▼           ▼          ▼         ▼
┌────────┐  ┌──────┐  ┌────────┐  ┌──────┐
│ Memory │  │ CPU  │  │Display │  │Timer │
│ (4KB)  │  │      │  │        │  │      │
└────────┘  └──────┘  └────────┘  └──────┘
    │           │          │         │
    └─────────────────────────────────┘
                  │
            ┌─────┴────────┐
            ▼              ▼
        ┌────────┐    ┌─────────┐
        │Keyboard│    │Registers│
        └────────┘    └─────────┘
```

## Componentes Principais

### 1. **Chip8.h** - Estrutura de Dados

```c
struct Chip8 {
    uint8_t memory[4096];              // RAM
    uint8_t registers[16];             // V0-VF
    uint16_t index_register;           // I
    uint16_t program_counter;          // PC
    uint16_t stack[16];                // Pilha
    uint8_t stack_pointer;             // SP
    uint8_t display[64*32];            // Tela
    uint8_t delay_timer;               // Timer de atraso
    uint8_t sound_timer;               // Timer de som
    uint8_t keys[16];                  // Teclado
};
```

**Tamanho Total**: ~5.5 KB

### 2. **Memory.c** - Gerenciamento de Memória

```
┌─────────────────┐
│ 0x000 - 0x050   │ Fontset (80 bytes)
├─────────────────┤
│ 0x050 - 0x1FF   │ Espaço livre (432 bytes)
├─────────────────┤
│ 0x200 - 0xFFF   │ ROM/Programa (3552 bytes)
└─────────────────┘
```

**Funções**:
- `memory_init()`: Carregar fontset
- `memory_read()`: Ler byte
- `memory_write()`: Escrever byte
- `memory_read_word()`: Ler 16 bits (opcode)

### 3. **CPU.c** - Núcleo de Execução

#### Ciclo Fetch-Decode-Execute

```c
void cpu_cycle() {
    1. Fetch:        opcode = memory[PC]
    2. Decode:       x, y, kk, nnn = parse(opcode)
    3. Execute:      switch(opcode & 0xF000)
    4. Update PC:    PC += 2
    5. Update Timer: delay_timer--
}
```

#### Instruções Implementadas (35 total)

**Categorias**:

| Código | Tipo | Exemplos |
|--------|------|----------|
| 0x0000 | Sistema | 00E0 (Clear), 00EE (Return) |
| 0x1000 | Fluxo | 1nnn (Jump), 2nnn (Call) |
| 0x3000-0x5000 | Condicional | 3xkk (Skip if ==) |
| 0x6000-0x8000 | Registrador | 6xkk (Set), 8xy4 (Add) |
| 0x9000 | Condicional | 9xy0 (Skip if !=) |
| 0xA000 | Índice | Annn (Set I) |
| 0xB000 | Fluxo | Bnnn (Jump with offset) |
| 0xC000 | Aleatório | Cxkk (Random) |
| 0xD000 | Draw | Dxyn (Draw sprite) |
| 0xE000 | Teclado | Ex9E, ExA1 |
| 0xF000 | Misc | Fx15, Fx33, Fx55, Fx65 |

### 4. **Display.c** - Renderização

```
┌────────────────────────────────────┐
│  Display Buffer (64x32 pixels)     │
│  ┌──────────────────────────────┐  │
│  │ Cada pixel = 1 bit (preto/branco) │
│  │ Armazenado em array linear   │
│  │ display[y * 64 + x]          │
│  └──────────────────────────────┘  │
└────────────────────────────────────┘
```

**Operações**:
- `display_clear()`: Limpar tela
- `display_set_pixel()`: Acender pixel
- `display_toggle_pixel()`: Alternar pixel (XOR)
- `display_render()`: Desenhar para tela (hook para gráficos)

### 5. **Keyboard.c** - Input

```
Mapa CHIP-8 (16 teclas hexadecimais):
┌───┬───┬───┬───┐
│ 1 │ 2 │ 3 │ C │
├───┼───┼───┼───┤
│ 4 │ 5 │ 6 │ D │
├───┼───┼───┼───┤
│ 7 │ 8 │ 9 │ E │
├───┼───┼───┼───┤
│ A │ 0 │ B │ F │
└───┴───┴───┴───┘

Array: keys[0x0] - keys[0xF]
```

**Funções**:
- `keyboard_press(key)`: Registrar tecla pressionada
- `keyboard_release(key)`: Registrar tecla liberada
- `keyboard_is_pressed(key)`: Verificar estado

### 6. **Timer.c** - Timers

```
Delay Timer:
- Usado para delay entre operações
- Decrementado a 60Hz
- Não para execução

Sound Timer:
- Usado para indicar som
- Decrementado a 60Hz
- Quando > 0, toca beep
```

**Funções**:
- `timer_tick()`: Decrementar (60Hz)
- `timer_set_delay()`: Configurar atraso
- `timer_set_sound()`: Configurar som

### 7. **Rom_Loader.c** - Carregamento

```c
int rom_load(chip8, "roms/game.ch8") {
    1. Abrir arquivo ROM
    2. Verificar tamanho (max 3552 bytes)
    3. Carregar em memory[0x200..]
    4. Fechar arquivo
}
```

## Fluxo de Execução Completo

```
┌─ main()
├─ chip8_init()
│  ├─ memory_init()     → Carregar fontset
│  ├─ display_init()    → Limpar display
│  ├─ keyboard_init()   → Zerar teclado
│  └─ timer_init()      → Zerar timers
│
├─ rom_load()           → Carregar ROM em memória
│
└─ for (cada ciclo)
   ├─ cpu_cycle()
   │  ├─ cpu_fetch()         → PC → Opcode
   │  ├─ cpu_decode_execute()
   │  │  ├─ Parsear: x, y, kk, nnn
   │  │  └─ switch (opcode & 0xF000)
   │  │      ├─ 0x0000: System
   │  │      ├─ 0x1000: Jump/Call
   │  │      ├─ 0x3000-0x5000: Skip
   │  │      ├─ 0x6000-0x8000: Register
   │  │      ├─ 0x9000: Skip not equal
   │  │      ├─ 0xA000: Set I
   │  │      ├─ 0xB000: Jump offset
   │  │      ├─ 0xC000: Random
   │  │      ├─ 0xD000: Draw sprite
   │  │      ├─ 0xE000: Keyboard
   │  │      └─ 0xF000: Misc
   │  └─ timer_tick()        → Decrementar timers
   │
   └─ display_render()      → Atualizar tela visual
```

## Exemplo: Executar Instrução 6x15

```c
opcode = 0x6115  // Set V1 = 0x15

x = (0x6115 >> 8) & 0x0F = 0x01
kk = 0x6115 & 0xFF = 0x15

switch (0x6115 & 0xF000) = case 0x6000:
    registers[0x01] = 0x15
    
PC += 2
```

## Extensibilidade

O design modular permite fácil expansão:

```
┌─────────────────┐
│  display.c      │ ← Integrar SDL2 aqui
│ display_render()│
└─────────────────┘

┌─────────────────┐
│   audio.c       │ ← Novo módulo para som
│  audio_beep()   │
└─────────────────┘

┌─────────────────┐
│  input.c        │ ← Novo módulo para controle
│  input_poll()   │
└─────────────────┘
```

---

**Estude o código** começando por `main.c` → `cpu.c` → módulos específicos.
