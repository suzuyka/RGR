#include "SuzuyaCipher.h"
#include "Utils.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Шифрование по байтам
vector<uint8_t> suzuyaEncrypt(const vector<uint8_t>& data, int shift, long long addNumber, bool showProcess) {
    vector<uint8_t> out(data.size());

    if (showProcess) {
        cout << "\n=== ШИФРОВАНИЕ ===\n";
        cout << "Сдвиг Цезаря: " << shift << "\n";
        cout << "Число для сложения: " << addNumber << "\n";
        cout << "Исходные данные (" << data.size() << " байт): ";
        for (auto b : data) cout << (int)b << " ";
        cout << "\n";
    }

    // 1) Цезарь
    for (size_t i = 0; i < data.size(); ++i) {
        out[i] = mod256((long long)data[i] + shift);
    }
    if (showProcess) {
        cout << "После Цезаря: ";
        for (auto b : out) cout << (int)b << " ";
        cout << "\n";
    }

    // 2) Реверс
    reverse(out.begin(), out.end());
    if (showProcess) {
        cout << "После реверса: ";
        for (auto b : out) cout << (int)b << " ";
        cout << "\n";
    }

    // 3) Сложение
    for (size_t i = 0; i < out.size(); ++i) {
        out[i] = mod256((long long)out[i] + addNumber);
    }
    if (showProcess) {
        cout << "После сложения: ";
        for (auto b : out) cout << (int)b << " ";
        cout << "\n";
    }

    return out;
}

// Дешифрование по байтам
vector<uint8_t> suzuyaDecrypt(const vector<uint8_t>& data, int shift, long long addNumber, bool showProcess) {
    vector<uint8_t> out(data.size());

    if (showProcess) {
        cout << "\n=== ДЕШИФРОВАНИЕ ===\n";
        cout << "Сдвиг Цезаря: " << shift << "\n";
        cout << "Число для вычитания: " << addNumber << "\n";
        cout << "Зашифрованные данные (" << data.size() << " байт): ";
        for (auto b : data) cout << (int)b << " ";
        cout << "\n";
    }

    // 1) Вычитание
    for (size_t i = 0; i < data.size(); ++i) {
        out[i] = mod256((long long)data[i] - addNumber);
    }
    if (showProcess) {
        cout << "После вычитания: ";
        for (auto b : out) cout << (int)b << " ";
        cout << "\n";
    }

    // 2) Реверс
    reverse(out.begin(), out.end());
    if (showProcess) {
        cout << "После реверса: ";
        for (auto b : out) cout << (int)b << " ";
        cout << "\n";
    }

    // 3) Обратный Цезарь
    for (size_t i = 0; i < out.size(); ++i) {
        out[i] = mod256((long long)out[i] - shift);
    }
    if (showProcess) {
        cout << "После обратного Цезаря: ";
        for (auto b : out) cout << (int)b << " ";
        cout << "\n";
    }

    return out;
}

// Шифрование текста
string encryptText(const string& text, int shift, long long addNumber, bool showProcess) {
    vector<uint8_t> bytes = stringToBytes(text);
    vector<uint8_t> enc = suzuyaEncrypt(bytes, shift, addNumber, showProcess);
    return bytesToString(enc);
}

// Дешифрование текста
string decryptText(const string& encrypted, int shift, long long addNumber, bool showProcess) {
    vector<uint8_t> bytes = stringToBytes(encrypted);
    vector<uint8_t> dec = suzuyaDecrypt(bytes, shift, addNumber, showProcess);
    return bytesToString(dec);
}
