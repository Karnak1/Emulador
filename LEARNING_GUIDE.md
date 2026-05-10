# 🎓 Guia de Aprendizado - Emulador CHIP-8

## Comece Aqui! 👋

Bem-vindo ao **Emulador CHIP-8 Modular em C**! 

Este é um projeto completo e didático sobre emulação de máquinas virtuais. Se você quer aprender como funcionam emuladores, compiladores ou máquinas virtuais, este é o lugar certo.

## 📚 Ordem de Leitura Recomendada

### Fase 1: Entender o Projeto (15 min)

1. **[QUICKSTART.md](QUICKSTART.md)** - Visão geral rápida
2. **[README.md](README.md)** - O que é CHIP-8?
3. **[PROJECT_SUMMARY.md](PROJECT_SUMMARY.md)** - O que foi implementado

### Fase 2: Entender o Design (30 min)

4. **[ARCHITECTURE.md](ARCHITECTURE.md)** - Como está organizado
   - Leia a "Visão Geral" (diagrama)
   - Leia cada componente principal
   - Estude o "Fluxo de Execução Completo"

### Fase 3: Estudar o Código (1-2 horas)

5. **Arquivo [include/chip8.h](include/chip8.h)** (5 min)
   - Entenda a estrutura principal
   - Memorize os campos

6. **Arquivo [src/main.c](src/main.c)** (15 min)
   - Leia `chip8_init()`
   - Leia o loop principal
   - Veja como é inicializado

7. **Arquivo [src/cpu.c](src/cpu.c)** (45 min) ⭐ IMPORTANTE
   - Leia `cpu_fetch()` - como buscar opcode
   - Leia `cpu_decode_and_execute()` - o coração
   - Estude alguns opcodes específicos:
     - `0x6000` (Set) - simples
     - `0x8000` (Operações) - um pouco mais complexo
     - `0xD000` (Draw) - mais complexo com XOR
     - `0xF000` (Misc) - avançado

8. **Outros módulos** (30 min)
   - [src/memory.c](src/memory.c) - Como acessar RAM
   - [src/display.c](src/display.c) - Buffer de pixels
   - [src/keyboard.c](src/keyboard.c) - Input simples
   - [src/timer.c](src/timer.c) - Timers 60Hz
   - [src/rom_loader.c](src/rom_loader.c) - Carregar ROM

### Fase 4: Compilar e Executar (30 min)

9. **[INSTALL.md](INSTALL.md)** - Instalar compilador
10. **Compilar**: `make` ou `gcc -std=c99 -I. src/*.c -o chip8_emulator`
11. **Testar**: `python3 create_test_rom.py && ./chip8_emulator roms/test.ch8`

## 🎯 Questões Para Guiar seu Aprendizado

Ao ler cada arquivo, tente responder:

### Sobre a Estrutura
- [ ] O que é a estrutura `Chip8`?
- [ ] Quantos registradores tem?
- [ ] Quantos bytes de memória?
- [ ] Como funciona o stack?

### Sobre a CPU
- [ ] O que significa "opcode"?
- [ ] Qual a diferença entre fetch, decode, execute?
- [ ] Por que PC incrementa de 2?
- [ ] Como são interpretadas as instruções?

### Sobre Instruções
- [ ] O que faz `6xkk`?
- [ ] Como funciona `8xy4`?
- [ ] Como é desenhado um sprite (`Dxyn`)?
- [ ] Como funciona a detecção de colisão?

### Sobre Memória
- [ ] Onde começa a ROM?
- [ ] Onde fica o fontset?
- [ ] Como é lido um opcode de 16 bits?

## 🔍 Exercícios Sugeridos

### Exercício 1: Entender um Opcode (30 min)
Escolha um opcode aleatório e:
1. Procure em `cpu.c`
2. Leia o comentário
3. Estude o código
4. Explique com suas próprias palavras

Exemplo: `8xy5` (Subtract with borrow)

### Exercício 2: Adicionar Debug (1 hora)
Modifique `src/main.c` para:
1. Imprimir registradores antes de cada instrução
2. Imprimir qual instrução vai ser executada
3. Imprimir resultado da execução

```c
printf("PC: 0x%04X | V0: 0x%02X | V1: 0x%02X\n", 
       chip8.program_counter, 
       chip8.registers[0], 
       chip8.registers[1]);
```

### Exercício 3: Criar Nova ROM (1.5 horas)
Use [create_test_rom.py](create_test_rom.py) como guia e crie:
1. Um programa que incrementa um registrador
2. Um programa que faz loop infinito
3. Um programa que chama uma subrotina

Dica: Estude a tabela de instruções em ARCHITECTURE.md

### Exercício 4: Integrar SDL2 (2-3 horas)
Use [examples/display_sdl2.c](examples/display_sdl2.c) para:
1. Integrar SDL2
2. Renderizar o display em tempo real
3. Mapear teclado para as 16 teclas CHIP-8

## 📖 Conceitos-Chave Para Aprender

### Emulação
- **Ciclo Fetch-Decode-Execute**: O coração de qualquer emulador
- **Opcode**: Instrução em formato binário
- **Registradores**: Memória ultra-rápida na CPU
- **Stack**: Pilha para chamadas de função

### Programação Baixo Nível
- **Máquinas de Estados**: Como a CPU funciona
- **Bitwise Operations**: AND, OR, XOR, shifts
- **Memory Management**: Alocação e acesso

### C Puro
- **Structs**: Organizando dados
- **Arrays**: Alocação fixa
- **Switch Statements**: Despacho eficiente
- **Ponteiros**: Acesso à memória

## 🛠️ Dicas de Estudo

1. **Compile Frequentemente**
   - Depois de entender um módulo, tente modificar e recompilar

2. **Use Printf Debug**
   ```c
   printf("DEBUG: Executed 0x%04X\n", opcode);
   ```

3. **Teste ROMs Simples Primeiro**
   - Crie testes que exercem poucas instruções

4. **Compare com Especificação**
   - http://devernay.free.fr/hacks/chip8/C8TECH10.HTM
   - Verifique se cada instrução está correta

5. **Escreva Notas**
   - Documente o que aprendeu em cada módulo
   - Faça diagramas

## 🎓 Recursos Externos

### Teorias
- [Write a CHIP-8 Emulator](https://tobiasvl.github.io/blog/write-a-chip-8-emulator/)
- [CHIP-8 Wikipedia](https://en.wikipedia.org/wiki/CHIP-8)
- [CHIP-8 Specification](http://devernay.free.fr/hacks/chip8/C8TECH10.HTM)

### Código
- [Emulador JavaScript](https://github.com/Zammy/chip8)
- [Emulador Python](https://github.com/kielgray/CHIP-8-Emulator)
- [Test ROMs](https://github.com/corax89/chip8-test-rom)

### Vídeos
- Procure por "Write a CHIP-8 Emulator" no YouTube
- Canais de emulação retro

## 🚀 Próximos Passos Após Dominar

Quando tiver confortável com o código:

1. **Implementar SDL2** → Visualização gráfica
2. **Adicionar Audio** → Som real
3. **Criar Debugger** → Breakpoints e stepping
4. **Otimizar** → Aumento de performance
5. **Expandir** → Emular outros sistemas (Game Boy, NES, etc)

## ✅ Checklist de Aprendizado

Marque conforme aprende:

### Compreensão Geral
- [ ] Entendi o que é CHIP-8
- [ ] Entendi o ciclo fetch-decode-execute
- [ ] Consigo explicar cada módulo

### Código C
- [ ] Entendo como funciona a estrutura `Chip8`
- [ ] Consigo rastrear uma instrução pelo código
- [ ] Entendo a lógica de despacho em `cpu.c`

### Emulação
- [ ] Sei como funciona um registrador
- [ ] Entendo a diferença entre opcode e instrução
- [ ] Consigo adicionar uma nova instrução

### Prático
- [ ] Consigo compilar o projeto
- [ ] Consigo executar uma ROM
- [ ] Consigo modificar o código e recompilar
- [ ] Consigo criar uma ROM teste simples

## 💡 Dicas Finais

> "A melhor forma de aprender emulação é estudando o código e experimentando."

1. **Leia o código Lentamente**
   - Não tente entender tudo de uma vez
   - Procure em um terminal conforme estuda

2. **Experimente**
   - Modifique valores
   - Veja o que acontece
   - Acerte os erros

3. **Peça Ajuda**
   - Stack Overflow
   - Comunidades de emulação retro
   - GitHub discussions

4. **Desista da Perfeição**
   - Não precisa entender 100%
   - Comece com 70% e melhore

---

**Estude bem! Se tiver dúvidas, consulte ARCHITECTURE.md ou os comentários no código.**

Boa sorte! 🍀
