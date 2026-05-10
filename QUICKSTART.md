# 🚀 Início Rápido

## Estrutura do Projeto

```
emulador/
├── 📄 README.md              ← Leia primeiro!
├── 📄 INSTALL.md             ← Instruções de compilação
├── 📄 ARCHITECTURE.md        ← Design detalhado
├── 📄 Makefile               ← Build system
├── 🐍 create_test_rom.py     ← Gerar ROM de teste
│
├── 📁 include/               ← Headers (.h)
│   ├── chip8.h              (Estrutura principal)
│   ├── cpu.h                (Processador)
│   ├── memory.h             (RAM)
│   ├── display.h            (Vídeo)
│   ├── keyboard.h           (Input)
│   ├── timer.h              (Timers)
│   └── rom_loader.h         (Carregador)
│
├── 📁 src/                   ← Implementações (.c)
│   ├── cpu.c                (35 instruções)
│   ├── memory.c             (4KB RAM + fontset)
│   ├── display.c            (Buffer de pixels)
│   ├── keyboard.c           (16 teclas)
│   ├── timer.c              (Delay + Sound)
│   ├── rom_loader.c         (Ler .ch8)
│   └── main.c               (Loop principal)
│
├── 📁 examples/
│   └── display_sdl2.c       (Integração gráfica)
│
└── 📁 roms/                  ← ROMs CHIP-8 aqui
    └── (vazio - coloque seus arquivos .ch8)
```

## Instalação Rápida

### 1️⃣ **Instalar Compilador C**

**Windows:**
- Baixar [MinGW-w64](https://www.mingw-w64.org/)
- Ou usar WSL (recomendado)
- Ou MSVC Build Tools

**Linux/macOS:**
```bash
sudo apt install build-essential  # Ubuntu/Debian
brew install gcc                 # macOS
```

### 2️⃣ **Compilar Emulador**

```bash
# Com Make (se instalado)
make

# Ou compilação manual
gcc -Wall -Wextra -std=c99 -I. src/*.c -o chip8_emulator
```

### 3️⃣ **Gerar/Obter ROM de Teste**

```bash
# Criar ROM simples
python3 create_test_rom.py

# Ou baixar ROMs prontas de:
# https://github.com/corax89/chip8-test-rom
# https://github.com/dmatlack/chip8/tree/master/roms
```

### 4️⃣ **Executar**

```bash
# Rodas ROM
./chip8_emulator roms/test.ch8

# Com limite de ciclos
./chip8_emulator roms/pong.ch8 500
```

## Próximas Etapas

### Phase 1: Validação ✅
- [x] Estrutura modular criada
- [x] Todas as 35 instruções CHIP-8 implementadas
- [x] Loader de ROM funcional

### Phase 2: Visualização 🎨
- [ ] Integrar SDL2 para janela gráfica
- [ ] Renderizar display em tempo real
- [ ] Mapear teclado (1-9, A-F)

### Phase 3: Audio 🔊
- [ ] Implementar beep simples com SDL_Audio
- [ ] Timer de som funcional

### Phase 4: Refinamento ⚡
- [ ] Sincronizar clock (~500 Hz)
- [ ] Debugger visual
- [ ] Testes com mais ROMs

## Teste Rápido (Sem Compilador)

Se não tiver compilador C instalado:

1. **Instale MinGW ou WSL**
2. Siga os passos acima
3. Leia `INSTALL.md` para detalhes

## Arquivos Importantes

| Arquivo | Propósito |
|---------|-----------|
| `include/chip8.h` | Estrutura da VM |
| `src/cpu.c` | Núcleo de execução |
| `src/main.c` | Loop principal |
| `README.md` | Documentação completa |
| `ARCHITECTURE.md` | Design em detalhes |

## Suporte

```bash
# Verificar compilador
gcc --version

# Compilar com saída de erro
gcc -v src/cpu.c 2>&1 | head -20

# Listar arquivos criados
ls -la
```

## Aprender Mais

1. 📖 Ler `ARCHITECTURE.md` para entender o design
2. 💻 Ler `src/cpu.c` para ver as instruções
3. 🔧 Modificar e expandir os módulos
4. 📚 Consultar [CHIP-8 Spec](http://devernay.free.fr/hacks/chip8/C8TECH10.HTM)

---

**Status**: ✅ Emulador base pronto para compilação e expansão!
