#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <fstream>

#include "SuzuyaCipher.h"
#include "TritemiusCipher.h"
#include "EnigmaCipher.h"
#include "Utils.h"

using namespace std;

void runSuzuyaCipher() {
    cout << "=== Шифр Цезаря с дополнительным сдвигом ===\n";

    // Выбор действия
    cout << "Выберите действие:\n1 - Зашифровать\n2 - Дешифровать\nВаш выбор: ";
    int action;
    cin >> action;
    cin.ignore();
    if (action != 1 && action != 2) { 
        cerr << "Некорректный выбор!\n"; 
        return; 
    }

    // Выбор источника
    cout << "Выберите источник:\n1 - Ввести текст вручную\n2 - Считать из файла\nВаш выбор: ";
    int inputChoice;
    cin >> inputChoice;
    cin.ignore();
    if (inputChoice != 1 && inputChoice != 2) {
        cerr << "Некорректный выбор источника!\n"; 
        return;
    }

    string inputText;
    vector<uint8_t> inputData;
    string filename;

    if (inputChoice == 1) {
        cout << "Введите текст: ";
        getline(cin, inputText);
    } else {
        cout << "Введите имя входного файла: ";
        getline(cin, filename);
        inputData = ReadFile(filename);
        if (inputData.empty()) {
            cerr << "Ошибка чтения файла или файл пустой.\n";
            return;
        }
        cout << "Файл успешно считан.\n";
    }

    // Параметры шифра
    int shift; 
    long long number;
    cout << "Введите сдвиг для шифра Цезаря: ";
    cin >> shift;
    cout << "Введите число для второго сдвига: ";
    cin >> number;
    cin.ignore();

    // Показ процесса
    cout << "Показывать процесс шифрования/дешифрования?\n1 - Да\n2 - Нет\nВаш выбор: ";
    int showProcess;
    cin >> showProcess;
    cin.ignore();
    if (showProcess != 1 && showProcess != 2) {
        cerr << "Некорректный выбор!\n";
        return;
    }
    bool show = (showProcess == 1);

    //обработка
    if (inputChoice == 1) {
        // текст
        string outputText = (action == 1) 
            ? encryptText(inputText, shift, number, show) 
            : decryptText(inputText, shift, number, show);

        // запись в файл
        string outFile = (action == 1 ? "encrypted_suzuya.txt" : "decrypted_suzuya.txt");
        vector<uint8_t> outputData(outputText.begin(), outputText.end());
        if (!WriteFile(outFile, outputData)) {
            cerr << "Ошибка записи в файл " << outFile << endl;
            return;
        }
        cout << "Результат записан в файл " << outFile << endl;

        if (show) {
            cout << "\nРЕЗУЛЬТАТ:\n" << outputText << endl;
        }

    } else {
        // бинарный файл
        vector<uint8_t> outputData = (action == 1) 
            ? suzuyaEncrypt(inputData, shift, number, show) 
            : suzuyaDecrypt(inputData, shift, number, show);

        string outFile = (action == 1 ? "encrypted_suzuya.bin" : "decrypted_suzuya.bin");
        if (!WriteFile(outFile, outputData)) {
            cerr << "Ошибка записи в файл " << outFile << endl;
            return;
        }
        cout << "Результат записан в файл " << outFile << endl;
    }
}

void runTritemiusCipher() {
    cout << "=== Шифр Тритемия ===\n";

    // Выбор действия
    cout << "Выберите действие:\n";
    cout << "1 - Зашифровать\n";
    cout << "2 - Дешифровать\n";
    cout << "Ваш выбор: ";
    int action;
    cin >> action;
    cin.ignore();

    if (action != 1 && action != 2) {
        cerr << "Некорректный выбор действия!\n";
        return;
    }

    // Выбор источника
    cout << "Выберите источник:\n";
    cout << "1: Ввести текст вручную\n";
    cout << "2: Считать из файла\n";
    cout << "Ваш выбор: ";
    int inputChoice;
    cin >> inputChoice;
    cin.ignore();

    string inputText;
    vector<uint8_t> inputData;

    if (inputChoice == 1) {
        cout << "Введите текст для обработки: ";
        getline(cin, inputText);
    }
    else if (inputChoice == 2) {
        cout << "Введите имя входного файла: ";
        string filename;
        getline(cin, filename);

        inputData = ReadFile(filename);
        if (inputData.empty()) {
            cerr << "Ошибка чтения файла или файл пустой.\n";
            return;
        }

        cout << "Файл успешно считан.\n";
    }
    else {
        cerr << "Неверный выбор!\n";
        return;
    }

    // Ввод коэффициентов полинома
    int degree;
    cout << "Введите степень функции для шифрования (1 - 5): ";
    cin >> degree;
    cin.ignore();

    if (degree < 1 || degree > 5) {
        cerr << "Степень должна быть от 1 до 5!\n";
        return;
    }

    vector<int> coeffs(degree + 1);
    cout << "Введите коэффициенты:\n";
    for (int i = 0; i <= degree; ++i) {
        cout << "Коэффициент при x^" << i << ": ";
        cin >> coeffs[i];
    }
    cin.ignore();

    cout << "Показывать процесс шифрования/дешифрования?\n";
    cout << "1 - Да\n2 - Нет\nВаш выбор: ";
    int showProcess;
    cin >> showProcess;
    cin.ignore();

    if (showProcess != 1 && showProcess != 2) {
        cerr << "Некорректный выбор!\n";
        return;
    }

    bool show = (showProcess == 1);

    // --- ввод вручную ---
    if (inputChoice == 1) {
        string outputText;
        if (action == 1)
            outputText = encryptText(inputText, coeffs, show);
        else
            outputText = decryptText(inputText, coeffs, show);

        // Всегда записываем в файл
        string filename = (action == 1 ? "encrypted_tritemius.txt" : "decrypted_tritemius.txt");
        vector<uint8_t> outputData(outputText.begin(), outputText.end());
        if (!WriteFile(filename, outputData)) {
            cerr << "Ошибка записи в файл\n";
            return;
        }
        cout << "Результат записан в файл " << filename << endl;

        if (show) {
            cout << "\nРЕЗУЛЬТАТ:\n" << outputText << endl;
        }
    }

    // --- бинарные данные ---
    else {
        vector<uint8_t> outputData;
        if (action == 1)
            outputData = encryptBytes(inputData, coeffs, show);
        else
            outputData = decryptBytes(inputData, coeffs, show);

        string filename = (action == 1 ? "encrypted_tritemius.bin" : "decrypted_tritemius.bin");
        if (!WriteFile(filename, outputData)) {
            cerr << "Ошибка записи\n";
            return;
        }
        cout << "Результат записан в файл " << filename << endl;
    }
}



void runEnigmaCipher() {
    cout << "=== Шифр Энигма ===\n";

    // Выбор действия
    cout << "Выберите действие:\n";
    cout << "1 - Зашифровать\n";
    cout << "2 - Дешифровать\n";
    cout << "Ваш выбор: ";
    int action;
    cin >> action;
    cin.ignore();

    if (action != 1 && action != 2) {
        cerr << "Некорректный выбор действия!\n";
        return;
    }

    // Выбор источника
    cout << "Выберите источник текста:\n";
    cout << "1: Ввести вручную\n";
    cout << "2: Считать из файла\n";
    cout << "Ваш выбор: ";
    int inputChoice;
    cin >> inputChoice;
    cin.ignore();

    string inputStr;

    if (inputChoice == 1) {
        cout << "Введите строку (латинские буквы): ";
        getline(cin, inputStr);
    } else if (inputChoice == 2) {
        cout << "Введите имя входного файла с текстом: ";
        string filename;
        getline(cin, filename);

        ifstream inputFile(filename);
        if (!inputFile) {
            cerr << "Не удалось открыть файл " << filename << endl;
            return;
        }
        inputStr = string((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());
        inputFile.close();

        cout << "Текст успешно считан из файла.\n";
    } else {
        cerr << "Неверный выбор источника текста!\n";
        return;
    }

    // Преобразуем к верхнему регистру
    transform(inputStr.begin(), inputStr.end(), inputStr.begin(), ::toupper);

    // Параметры шифра
    string alphabetUPPER = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string ROTOR1UPPER = "EKMFLGDQVZNTOWYHXUSPAIBRCJ";
    string ROTOR2UPPER = "AJDKSIRUXBLHWTMCQGZNPYFVOE";
    string ROTOR3UPPER = "BDFHJLCPRTXVZNYEIWGAKMUSQO";
    string REFLBUPPER = "YRUHQSLDPXNGOKMIEBFZCWVJAT";

    int ring1 = 0, ring2 = 0, ring3 = 0;
    vector<int> ROTORSbegin(3, 0);
    vector<pair<int32_t, char>> nonPrintableSymbols;

    cout << "Показывать процесс шифрования/дешифрования?\n";
    cout << "1 - Да\n";
    cout << "2 - Нет\n";
    cout << "Ваш выбор: ";
    int showProcess;
    cin >> showProcess;
    cin.ignore();

    if (showProcess != 1 && showProcess != 2) {
        cerr << "Некорректный выбор отображения процесса!\n";
        return;
    }

    string resultText;

    bool show = (showProcess == 1);
    if (action == 1) {  // Зашифровать
        resultText = enigmaCipherEncr(inputStr, alphabetUPPER, nonPrintableSymbols,
                                      ROTORSbegin, ROTOR1UPPER, ROTOR2UPPER, ROTOR3UPPER,
                                      REFLBUPPER, ring1, ring2, ring3, show);

        if (showProcess == 1) {
            cout << "\nЗашифрованный текст: " << resultText << endl;
        } else {
            // Тихий режим
            ofstream outFile("encrypted_enigma.txt");
            if (outFile) {
                outFile << resultText;
                cout << "Зашифрованный текст записан в файл encrypted_enigma.txt\n";
            } else {
                cerr << "Ошибка: не удалось открыть файл encrypted_enigma.txt для записи\n";
            }
            return;
        }

    } else {  
        ROTORSbegin = {0, 0, 0};
        resultText = enigmaCipherDecr(inputStr, alphabetUPPER, ROTORSbegin,
                                      ROTOR1UPPER, ROTOR2UPPER, ROTOR3UPPER,
                                      REFLBUPPER, ring1, ring2, ring3, show);

        // Восстанавливаем символы
        for (int i = 0; i < static_cast<int>(inputStr.size()); ++i) {
            for (const auto& c : nonPrintableSymbols) {
                if (c.first == i) {
                    resultText.insert(c.first, 1, c.second);
                    i++;
                }
            }
        }

        if (showProcess == 1) {
            cout << "\nРасшифрованный текст: " << resultText << endl;
        } else {
            // Тихий режим
            ofstream outFile("decrypted_enigma.txt");
            if (outFile) {
                outFile << resultText;
                cout << "Дешифрованный текст записан в файл decrypted_enigma.txt\n";
            } else {
                cerr << "Ошибка: не удалось открыть файл decrypted_enigma.txt для записи\n";
            }
            return;
        }
    }

    cout << "\n" << string(50, '=') << endl;
    cout << "РЕЗУЛЬТАТ:\n";
    cout << "Исходный текст:      " << inputStr << endl;
    cout << (action == 1 ? "Зашифрованный текст: " : "Расшифрованный текст: ") << resultText << endl;
}

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");

    while (true) {
        cout << "\nВыберите шифр для работы:\n";
        cout << "1: Шифр Цезаря с сдвигом(шифр Сузуи Джузо)\n";
        cout << "2: Шифр Тритемия\n";
        cout << "3: Шифр Энигма\n";
        cout << "0: Выход\n";
        cout << "Ваш выбор: ";

        int choice;
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                runSuzuyaCipher();
                break;
            case 2:
                runTritemiusCipher();
                break;
            case 3:
                runEnigmaCipher();
                break;
            case 0:
                cout << "Выход из программы.\n";
                return 0;
            default:
                cout << "Некорректный выбор. Попробуйте снова.\n";
        }
    }

    return 0;
}
