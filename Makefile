CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -I.
LDFLAGS = 

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = .

SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SOURCES))
EXECUTABLE = $(BIN_DIR)/chip8_emulator

# Target padrão
all: $(EXECUTABLE)

# Compilar executável
$(EXECUTABLE): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	@echo "✓ Emulador compilado com sucesso: $(EXECUTABLE)"

# Compilar arquivos objeto
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Executar emulador com ROM exemplo
run: $(EXECUTABLE)
	@if [ -f "roms/pong.ch8" ]; then \
		$(EXECUTABLE) roms/pong.ch8 50; \
	else \
		echo "Aviso: roms/pong.ch8 não encontrado"; \
		echo "Coloque uma ROM CHIP-8 em roms/"; \
	fi

# Limpeza
clean:
	rm -rf $(OBJ_DIR) $(EXECUTABLE)
	@echo "✓ Limpeza concluída"

# Ajuda
help:
	@echo "Alvos disponíveis:"
	@echo "  make              - Compilar emulador"
	@echo "  make run          - Compilar e executar com ROM exemplo"
	@echo "  make clean        - Remover arquivos compilados"
	@echo "  make help         - Mostrar esta mensagem"

.PHONY: all run clean help
