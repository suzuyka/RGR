#!/bin/bash

DESKTOP_DIR=$(xdg-user-dir DESKTOP)
DEST="$DESKTOP_DIR/encrypt-decrypt"
DESKTOP_FILE="$DESKTOP_DIR/cipher_tool.desktop"

echo "[+] Деинсталляция cipher_tool..."

# Проверяем, установлен ли ярлык
if [ ! -f "$DESKTOP_FILE" ] && [ ! -d "$DEST" ]; then
    echo "[!] Программа не найдена. Возможно, она уже удалена."
    exit 1
fi

# Удаляем папку с программой
if [ -d "$DEST" ]; then
    echo "[*] Удаление папки: $DEST"
    rm -rf "$DEST"
    echo "[✓] Папка удалена"
else
    echo "[-] Папка $DEST не найдена"
fi

# Удаляем .desktop файл
if [ -f "$DESKTOP_FILE" ]; then
    echo "[*] Удаление ярлыка: $DESKTOP_FILE"
    rm -f "$DESKTOP_FILE"
    echo "[✓] Ярлык удален"
else
    echo "[-] Ярлык $DESKTOP_FILE не найден"
fi

# Ищем и удаляем возможные остаточные файлы
RESIDUAL_SCRIPT="$DESKTOP_DIR/run_cipher.sh"
if [ -f "$RESIDUAL_SCRIPT" ]; then
    echo "[*] Удаление остаточного файла: $RESIDUAL_SCRIPT"
    rm -f "$RESIDUAL_SCRIPT"
fi

echo "[✓] Деинсталляция завершена!"
