#!/usr/bin/env python3
"""
Gerador de ROM CHIP-8 de teste simples
Cria um programa que testa as funcionalidades básicas do emulador
"""

def create_test_rom():
    """Criar ROM de teste simples"""
    
    # Instruções CHIP-8 (bytecode)
    instructions = [
        # Inicializar display (limpar)
        (0x00, 0xE0),  # 00E0 - Clear display
        
        # Carregar valor em V0
        (0x60, 0x10),  # 6010 - Set V0 = 0x10
        
        # Carregar índice
        (0xA1, 0x23),  # A123 - Set I = 0x123
        
        # Adicionar número aleatório
        (0xC0, 0xFF),  # C0FF - Set V0 = random() & 0xFF
        
        # Desenhar um sprite simples (8x8)
        (0xD0, 0x08),  # D008 - Draw sprite at (V0, 0) with height 8
        
        # Delay
        (0xF0, 0x15),  # F015 - Set delay_timer = V0
        
        # Loop infinito
        (0x12, 0x06),  # 1206 - Jump to 0x206
    ]
    
    with open('roms/test.ch8', 'wb') as f:
        for high, low in instructions:
            f.write(bytes([high, low]))
    
    print("✓ ROM de teste criada: roms/test.ch8")

if __name__ == '__main__':
    create_test_rom()
