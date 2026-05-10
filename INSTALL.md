# 🔧 Guia de Instalação e Compilação

## Windows

### Opção 1: MinGW (Recomendado)

1. **Baixar MinGW-w64**
   - Acesse: https://www.mingw-w64.org/
   - Download: [x86_64 version](https://sourceforge.net/projects/mingw-w64/files/)
   - Extrair para: `C:\MinGW\` (ou local de sua escolha)

2. **Adicionar ao PATH do Windows**
   - Variáveis de Ambiente → Editar
   - Nova variável: `MINGW_HOME = C:\MinGW\mingw64\bin`
   - Adicionar ao PATH: `;%MINGW_HOME%`
   - Reiniciar Terminal

3. **Compilar**
   ```bash
   make
   # Ou sem Make:
   gcc -Wall -Wextra -std=c99 -I. src/*.c -o chip8_emulator.exe
   ```

### Opção 2: Microsoft Visual C++ Build Tools

1. **Instalar MSVC**
   - Download: https://visualstudio.microsoft.com/visual-cpp-build-tools/
   - Abrir "x64 Native Tools Command Prompt"

2. **Compilar com CL.exe**
   ```bash
   cl /W4 /std:c17 /I. src\*.c /Fe:chip8_emulator.exe
   ```

### Opção 3: WSL (Windows Subsystem for Linux)

1. **Instalar WSL2**
   ```powershell
   wsl --install
   ```

2. **Dentro do WSL, instalar GCC**
   ```bash
   sudo apt update && sudo apt install build-essential
   ```

3. **Compilar**
   ```bash
   make
   ```

## Linux / macOS

### Instalar dependências
```bash
sudo apt install build-essential  # Ubuntu/Debian
# ou
brew install gcc               # macOS
```

### Compilar
```bash
make
# Ou
gcc -Wall -Wextra -std=c99 -I. src/*.c -o chip8_emulator
```

## Compilação Manual (sem Make)

### Windows (PowerShell)
```powershell
gcc -Wall -Wextra -std=c99 -I. src\*.c -o chip8_emulator.exe
```

### Linux / macOS
```bash
gcc -Wall -Wextra -std=c99 -I. src/*.c -o chip8_emulator
```

## Verificar Instalação

```bash
# Verificar GCC
gcc --version

# Compilar programa teste
gcc -Wall -std=c99 -c src/memory.c -o memory.o

# Linkar tudo
gcc -o chip8_emulator obj/*.o
```

## Próximas Etapas

1. ✅ Instalar compilador C
2. 📦 Compilar projeto: `make`
3. 🎮 Gerar ROM teste: `python3 create_test_rom.py`
4. ▶️ Executar: `./chip8_emulator roms/test.ch8`

---

**Suporte**: Se tiver dúvidas, execute em um terminal:
```bash
gcc --version
echo %PATH%  # Windows
echo $PATH   # Linux/macOS
```
