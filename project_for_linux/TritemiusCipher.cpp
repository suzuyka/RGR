#include "TritemiusCipher.h"
#include "Utils.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Вычисление функции k(x)
int64_t kFunction(int x, const vector<int>& coeffs) {
    int64_t result = 0;
    int64_t power = 1;

    for (int coeff : coeffs) {
        result += coeff * power;
        power *= x;
    }

    return result;
}

// Сдвиг для текстовых символов
uint32_t tritemiusCipher(uint32_t code, uint32_t position, int64_t shift) {
    const uint32_t maxUnicode = 0x10FFFF;

    int64_t shifted = (static_cast<int64_t>(code) + static_cast<int64_t>(position) + shift) % (maxUnicode + 1);
    if (shifted < 0) shifted += (maxUnicode + 1);

    return static_cast<uint32_t>(shifted);
}

// Обратный сдвиг
uint32_t reverseTritemius(uint32_t code, uint32_t position, int64_t shift) {
    const uint32_t maxUnicode = 0x10FFFF;

    int64_t shifted = (static_cast<int64_t>(code) - static_cast<int64_t>(position) - shift) % (maxUnicode + 1);
    if (shifted < 0) shifted += (maxUnicode + 1);

    return static_cast<uint32_t>(shifted);
}

// --- Шифрование текста ---
string encryptText(const string& text, const vector<int>& coeffs, bool showProcess) {
    if(showProcess) {
        cout << "\n=== ШИФРОВАНИЕ ===\nИсходный текст: " << text << endl;
    }

    string encryptedText(text.size(), '\0');

    for (size_t pos = 0; pos < text.size(); ++pos) {
        int64_t shift = kFunction(static_cast<int>(pos), coeffs);
        encryptedText[pos] = static_cast<char>(mod256(static_cast<unsigned char>(text[pos]) + shift));
    }

    if(showProcess) {
        cout << "Зашифрованные байты: ";
        for (unsigned char c : encryptedText) cout << static_cast<int>(c) << " ";
        cout << endl;
    }

    return encryptedText;
}

// --- Дешифрование текста ---
string decryptText(const string& text, const vector<int>& coeffs, bool showProcess) {
    if(showProcess) {
        cout << "\n=== ДЕШИФРОВАНИЕ ===\nИсходный текст: " << text << endl;
    }

    string decryptedText(text.size(), '\0');

    for (size_t pos = 0; pos < text.size(); ++pos) {
        int64_t shift = kFunction(static_cast<int>(pos), coeffs);
        decryptedText[pos] = static_cast<char>(mod256(static_cast<unsigned char>(text[pos]) - shift));
    }

    if(showProcess) {
        cout << "Дешифрованные байты: ";
        for (unsigned char c : decryptedText) cout << static_cast<int>(c) << " ";
        cout << endl;
    }

    return decryptedText;
}


// --- Шифрование бинарных данных ---
vector<uint8_t> encryptBytes(const vector<uint8_t>& data, const vector<int>& coeffs, bool showProcess) {
    if (showProcess) {
        cout << "\n=== ШИФРОВАНИЕ ===\nИсходные данные: ";
        for (uint8_t b : data) cout << static_cast<int>(b) << " ";
        cout << endl;
    }

    vector<uint8_t> out(data.size());

    for (size_t pos = 0; pos < data.size(); ++pos) {
        int64_t shift = kFunction(static_cast<int>(pos), coeffs);
        out[pos] = mod256(data[pos] + shift);
    }

    if (showProcess) {
        cout << "Зашифрованные байты: ";
        for (uint8_t b : out) cout << static_cast<int>(b) << " ";
        cout << endl;
    }

    return out;
}

// --- Дешифрование бинарных данных ---
vector<uint8_t> decryptBytes(const vector<uint8_t>& data, const vector<int>& coeffs, bool showProcess) {
    if (showProcess) {
        cout << "\n=== ДЕШИФРОВАНИЕ ===\nИсходные данные: ";
        for (uint8_t b : data) cout << static_cast<int>(b) << " ";
        cout << endl;
    }

    vector<uint8_t> out(data.size());

    for (size_t pos = 0; pos < data.size(); ++pos) {
        int64_t shift = kFunction(static_cast<int>(pos), coeffs);
        out[pos] = mod256(data[pos] - shift);
    }

    if (showProcess) {
        cout << "Дешифрованные байты: ";
        for (uint8_t b : out) cout << static_cast<int>(b) << " ";
        cout << endl;
    }

    return out;
}

