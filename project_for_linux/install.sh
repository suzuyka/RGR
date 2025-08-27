#!/bin/bash
set -e

DESKTOP_DIR=$(xdg-user-dir DESKTOP)
DEST="$DESKTOP_DIR/encrypt-decrypt"
DESKTOP_FILE="$DESKTOP_DIR/cipher_tool.desktop"

echo "[+] Установка cipher_tool..."

# Проверка: есть ли .cpp файлы?
if [ ! -f "main.cpp" ]; then
    echo "[!] Ошибка: файл 'main.cpp' не найден."
    echo "Убедитесь, что вы запускаете скрипт из папки с исходным кодом."
    exit 1
fi

# Удаляем старую версию
rm -rf "$DEST"
rm -f "$DESKTOP_FILE"

# Создаём папку build
mkdir -p "$DEST/build"

# Компилируем программу
g++ -std=c++17 -O2 -Wall *.cpp -o "$DEST/build/encrypt_decrypt"

# Создаём run.sh
cat > "$DEST/run.sh" <<'EOF'
#!/bin/bash
cd "$(dirname "$0")/build"
./encrypt_decrypt
EOF
chmod +x "$DEST/run.sh"

# Создаём .desktop ярлык с правильным экранированием пробелов
cat > "$DESKTOP_FILE" <<EOF
[Desktop Entry]
Version=1.0
Name=cipher_tool
Comment=Шифрование и дешифрование файлов
Exec=/bin/bash "$DEST/run.sh"
Icon=utilities-terminal
Terminal=true
Type=Application
Categories=Utility;
StartupNotify=true
EOF

# Делаем .desktop файл исполняемым
chmod +x "$DESKTOP_FILE"

echo "[✓] Установка завершена!"
echo "Папка: $DEST"
echo "Ярлык: $DESKTOP_FILE"
echo ""
echo "🔹 Дважды кликните по ярлыку для запуска программы."
