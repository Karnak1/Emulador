#!/usr/bin/env python3
"""
Verificador de integridade do projeto Emulador CHIP-8
Valida que todos os arquivos foram criados corretamente
"""

import os
import sys

REQUIRED_FILES = {
    # Headers
    'include/chip8.h': 'Estrutura principal',
    'include/cpu.h': 'Interface CPU',
    'include/memory.h': 'Interface memória',
    'include/display.h': 'Interface display',
    'include/keyboard.h': 'Interface teclado',
    'include/timer.h': 'Interface timer',
    'include/rom_loader.h': 'Interface ROM loader',
    
    # Implementação
    'src/main.c': 'Loop principal',
    'src/cpu.c': 'CPU (35 instruções)',
    'src/memory.c': 'Gerenciar RAM',
    'src/display.c': 'Buffer de pixels',
    'src/keyboard.c': 'Entrada',
    'src/timer.c': 'Timers',
    'src/rom_loader.c': 'Carregador ROM',
    
    # Build
    'Makefile': 'Sistema de compilação',
    
    # Utilitários
    'create_test_rom.py': 'Gerador ROM teste',
    
    # Documentação
    'README.md': 'Documentação principal',
    'QUICKSTART.md': 'Início rápido',
    'INSTALL.md': 'Instruções instalação',
    'ARCHITECTURE.md': 'Documentação arquitetura',
    'PROJECT_SUMMARY.md': 'Resumo projeto',
}

REQUIRED_DIRS = [
    'include',
    'src',
    'roms',
    'examples',
]

def check_files():
    """Verificar se todos os arquivos existem"""
    print("🔍 Verificando arquivos do projeto...\n")
    
    missing = []
    found = []
    
    for filepath, description in REQUIRED_FILES.items():
        full_path = os.path.join(os.path.dirname(__file__), filepath)
        if os.path.exists(full_path):
            size = os.path.getsize(full_path)
            found.append((filepath, description, size))
            print(f"✅ {filepath:30} ({size:5d} bytes) - {description}")
        else:
            missing.append(filepath)
            print(f"❌ {filepath:30} - FALTANDO!")
    
    return found, missing

def check_directories():
    """Verificar se todos os diretórios existem"""
    print("\n📁 Verificando diretórios...\n")
    
    missing_dirs = []
    
    for dirname in REQUIRED_DIRS:
        full_path = os.path.join(os.path.dirname(__file__), dirname)
        if os.path.isdir(full_path):
            print(f"✅ {dirname:20} - OK")
        else:
            missing_dirs.append(dirname)
            print(f"❌ {dirname:20} - FALTANDO!")
    
    return missing_dirs

def count_lines():
    """Contar linhas de código"""
    print("\n📊 Contando linhas de código...\n")
    
    total_lines = 0
    
    c_files = []
    h_files = []
    doc_files = []
    
    for filepath in REQUIRED_FILES.keys():
        full_path = os.path.join(os.path.dirname(__file__), filepath)
        
        if not os.path.exists(full_path):
            continue
        
        with open(full_path, 'r', encoding='utf-8', errors='ignore') as f:
            lines = len(f.readlines())
        
        total_lines += lines
        
        if filepath.endswith('.c'):
            c_files.append((filepath, lines))
        elif filepath.endswith('.h'):
            h_files.append((filepath, lines))
        elif filepath.endswith('.md'):
            doc_files.append((filepath, lines))
    
    print("📝 Arquivos C:")
    c_total = 0
    for fname, lines in c_files:
        print(f"  {fname:25} {lines:4d} linhas")
        c_total += lines
    
    print(f"\n  Total C: {c_total} linhas")
    
    print("\n📑 Headers:")
    h_total = 0
    for fname, lines in h_files:
        print(f"  {fname:25} {lines:4d} linhas")
        h_total += lines
    
    print(f"\n  Total Headers: {h_total} linhas")
    
    print(f"\n📚 Documentação: {sum(l for _, l in doc_files)} linhas")
    
    print(f"\n📊 TOTAL: {total_lines} linhas de código + docs\n")
    
    return total_lines

def print_summary(found, missing, missing_dirs):
    """Imprimir resumo final"""
    print("=" * 60)
    print("📋 RESUMO DO PROJETO")
    print("=" * 60)
    
    print(f"\n✅ Arquivos criados: {len(found)}/{len(REQUIRED_FILES)}")
    print(f"✅ Diretórios criados: {len(REQUIRED_DIRS) - len(missing_dirs)}/{len(REQUIRED_DIRS)}")
    
    if missing or missing_dirs:
        print(f"\n❌ FALTANDO:")
        for f in missing:
            print(f"   - {f}")
        for d in missing_dirs:
            print(f"   - {d}/")
        return False
    
    print("\n🎉 PROJETO COMPLETO! Todos os arquivos foram criados com sucesso!")
    print("\n📝 Próximos passos:")
    print("   1. Instale compilador C (gcc, mingw ou msvc)")
    print("   2. Execute: make")
    print("   3. Execute: python3 create_test_rom.py")
    print("   4. Execute: ./chip8_emulator roms/test.ch8")
    
    return True

def main():
    """Função principal"""
    found, missing = check_files()
    missing_dirs = check_directories()
    
    count_lines()
    
    success = print_summary(found, missing, missing_dirs)
    
    sys.exit(0 if success else 1)

if __name__ == '__main__':
    main()
