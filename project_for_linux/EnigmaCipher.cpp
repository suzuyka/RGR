#include "EnigmaCipher.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

string enigmaCipherEncr(const string& inputStr, const string& alphabetUPPER,
                        vector<pair<int32_t,char>>& nonPrintableSymbols,
                        vector<int> ROTORSbegin,
                        const string& ROTOR1UPPER,
                        const string& ROTOR2UPPER,
                        const string& ROTOR3UPPER,
                        const string& REFLBUPPER,
                        int ring1, int ring2, int ring3,
                        bool showProcess)
{
    if (showProcess) {
        cout << "\n=== ПРЕДУПРЕЖДЕНИЕ ===\nОбрабатываются только латинские буквы!\n\n";
        cout << "Длина строки: " << inputStr.size() << endl;
    }

    string result = "";

    for (size_t j = 0; j < inputStr.size(); j++) {
        int number = alphabetUPPER.find(inputStr[j]);
        if (number < 0) {
            nonPrintableSymbols.push_back(make_pair(j, inputStr[j]));
            continue;
        }

        if (showProcess) cout << "\n=== Обработка буквы: " << inputStr[j] << " ===" << endl;
        if (showProcess) cout << "Позиция буквы " << inputStr[j] << " в алфавите: " << number << endl;

        ROTORSbegin[2] = (ROTORSbegin[2] + 1) % 26;
        if (ROTORSbegin[2] == 0) {
            ROTORSbegin[1] = (ROTORSbegin[1] + 1) % 26;
            if (ROTORSbegin[1] == 0) {
                ROTORSbegin[0] = (ROTORSbegin[0] + 1) % 26;
            }
        }

        if (showProcess) cout << "Позиции роторов: " << char('A' + ROTORSbegin[0]) << " "
                              << char('A' + ROTORSbegin[1]) << " "
                              << char('A' + ROTORSbegin[2]) << endl;

        int pos3 = ROTORSbegin[2];
        int step3 = (number + pos3 - ring3 + 26) % 26;
        char letter3 = ROTOR3UPPER[step3];
        int map3 = alphabetUPPER.find(letter3);
        int out3 = (map3 - pos3 + ring3 + 26) % 26;
        if (showProcess) cout << "Ротор 3: " << setw(2) << step3 << " " << letter3 << " " << map3 << " " << out3 << endl;

        int pos2 = ROTORSbegin[1];
        int step2 = (out3 + pos2 - ring2 + 26) % 26;
        char letter2 = ROTOR2UPPER[step2];
        int map2 = alphabetUPPER.find(letter2);
        int out2 = (map2 - pos2 + ring2 + 26) % 26;
        if (showProcess) cout << "Ротор 2: " << setw(2) << step2 << " " << letter2 << " " << map2 << " " << out2 << endl;

        int pos1 = ROTORSbegin[0];
        int step1 = (out2 + pos1 - ring1 + 26) % 26;
        char letter1 = ROTOR1UPPER[step1];
        int map1 = alphabetUPPER.find(letter1);
        int out1 = (map1 - pos1 + ring1 + 26) % 26;
        if (showProcess) cout << "Ротор 1: " << setw(2) << step1 << " " << letter1 << " " << map1 << " " << out1 << endl;

        int refl = REFLBUPPER.find(alphabetUPPER[out1]);
        if (showProcess) cout << "Отражатель: " << setw(2) << refl << " " << REFLBUPPER[out1] << endl;

        int stepBack1 = (refl + pos1 - ring1 + 26) % 26;
        char targetChar1 = alphabetUPPER[stepBack1];
        int mapBack1 = -1;
        for (size_t k = 0; k < ROTOR1UPPER.size(); k++) {
            if (ROTOR1UPPER[k] == targetChar1) {
                mapBack1 = (int)k;
                break;
            }
        }
        int outBack1 = (mapBack1 - pos1 + ring1 + 26) % 26;
        if (showProcess) cout << "Обратно 1: " << setw(2) << stepBack1 << " " << targetChar1 << " "
                              << mapBack1 << " " << outBack1 << endl;

        int stepBack2 = (outBack1 + pos2 - ring2 + 26) % 26;
        char targetChar2 = alphabetUPPER[stepBack2];
        int mapBack2 = -1;
        for (size_t k = 0; k < ROTOR2UPPER.size(); k++) {
            if (ROTOR2UPPER[k] == targetChar2) {
                mapBack2 = (int)k;
                break;
            }
        }
        int outBack2 = (mapBack2 - pos2 + ring2 + 26) % 26;
        if (showProcess) cout << "Обратно 2: " << setw(2) << stepBack2 << " " << targetChar2 << " "
                              << mapBack2 << " " << outBack2 << endl;

        int stepBack3 = (outBack2 + pos3 - ring3 + 26) % 26;
        char targetChar3 = alphabetUPPER[stepBack3];
        int mapBack3 = -1;
        for (size_t k = 0; k < ROTOR3UPPER.size(); k++) {
            if (ROTOR3UPPER[k] == targetChar3) {
                mapBack3 = (int)k;
                break;
            }
        }
        int outBack3 = (mapBack3 - pos3 + ring3 + 26) % 26;
        if (showProcess) cout << "Обратно 3: " << setw(2) << stepBack3 << " " << targetChar3 << " "
                              << mapBack3 << " " << outBack3 << endl;

        char finalChar = alphabetUPPER[outBack3];
        result += finalChar;

        if (showProcess) cout << "Результат: " << finalChar << endl;
    }

    if (showProcess) {
        cout << "\n=== ИТОГ ===" << endl;
        cout << "Исходная строка: " << inputStr << endl;
        cout << "Выходная строка: " << result << endl;
    }

    return result;
}


string enigmaCipherDecr(const string& cipherText, const string& alphabetUPPER,
                        vector<int> ROTORSbegin,
                        const string& ROTOR1UPPER,
                        const string& ROTOR2UPPER,
                        const string& ROTOR3UPPER,
                        const string& REFLBUPPER,
                        int ring1, int ring2, int ring3,
                        bool showProcess)
{
    if (showProcess) cout << "Длина строки: " << cipherText.size() << endl;

    string resultEncr = "";

    for (size_t j = 0; j < cipherText.size(); j++) {
        int number = alphabetUPPER.find(cipherText[j]);
        if (number < 0) continue;

        if (showProcess) cout << "\n=== Обработка буквы: " << cipherText[j] << " ===" << endl;
        if (showProcess) cout << "Позиция буквы " << cipherText[j] << " в алфавите: " << number << endl;

        ROTORSbegin[2] = (ROTORSbegin[2] + 1) % 26;
        if (ROTORSbegin[2] == 0) {
            ROTORSbegin[1] = (ROTORSbegin[1] + 1) % 26;
            if (ROTORSbegin[1] == 0) {
                ROTORSbegin[0] = (ROTORSbegin[0] + 1) % 26;
            }
        }

        if (showProcess) cout << "Позиции роторов: " << char('A' + ROTORSbegin[0]) << " "
                              << char('A' + ROTORSbegin[1]) << " "
                              << char('A' + ROTORSbegin[2]) << endl;

        int pos3 = ROTORSbegin[2];
        int step3 = (number + pos3 - ring3 + 26) % 26;
        char letter3 = ROTOR3UPPER[step3];
        int map3 = alphabetUPPER.find(letter3);
        int out3 = (map3 - pos3 + ring3 + 26) % 26;
        if (showProcess) cout << "Ротор 3: " << setw(2) << step3 << " " << letter3 << " " << map3 << " " << out3 << endl;

        int pos2 = ROTORSbegin[1];
        int step2 = (out3 + pos2 - ring2 + 26) % 26;
        char letter2 = ROTOR2UPPER[step2];
        int map2 = alphabetUPPER.find(letter2);
        int out2 = (map2 - pos2 + ring2 + 26) % 26;
        if (showProcess) cout << "Ротор 2: " << setw(2) << step2 << " " << letter2 << " " << map2 << " " << out2 << endl;

        int pos1 = ROTORSbegin[0];
        int step1 = (out2 + pos1 - ring1 + 26) % 26;
        char letter1 = ROTOR1UPPER[step1];
        int map1 = alphabetUPPER.find(letter1);
        int out1 = (map1 - pos1 + ring1 + 26) % 26;
        if (showProcess) cout << "Ротор 1: " << setw(2) << step1 << " " << letter1 << " " << map1 << " " << out1 << endl;

        int refl = REFLBUPPER.find(alphabetUPPER[out1]);
        if (showProcess) cout << "Отражатель: " << setw(2) << refl << " " << REFLBUPPER[out1] << endl;

        int stepBack1 = (refl + pos1 - ring1 + 26) % 26;
        char targetChar1 = alphabetUPPER[stepBack1];
        int mapBack1 = -1;
        for (size_t k = 0; k < ROTOR1UPPER.size(); k++) {
            if (ROTOR1UPPER[k] == targetChar1) {
                mapBack1 = (int)k;
                break;
            }
        }
        int outBack1 = (mapBack1 - pos1 + ring1 + 26) % 26;
        if (showProcess) cout << "Обратно 1: " << setw(2) << stepBack1 << " " << targetChar1 << " "
                              << mapBack1 << " " << outBack1 << endl;

        int stepBack2 = (outBack1 + pos2 - ring2 + 26) % 26;
        char targetChar2 = alphabetUPPER[stepBack2];
        int mapBack2 = -1;
        for (size_t k = 0; k < ROTOR2UPPER.size(); k++) {
            if (ROTOR2UPPER[k] == targetChar2) {
                mapBack2 = (int)k;
                break;
            }
        }
        int outBack2 = (mapBack2 - pos2 + ring2 + 26) % 26;
        if (showProcess) cout << "Обратно 2: " << setw(2) << stepBack2 << " " << targetChar2 << " "
                              << mapBack2 << " " << outBack2 << endl;

        int stepBack3 = (outBack2 + pos3 - ring3 + 26) % 26;
        char targetChar3 = alphabetUPPER[stepBack3];
        int mapBack3 = -1;
        for (size_t k = 0; k < ROTOR3UPPER.size(); k++) {
            if (ROTOR3UPPER[k] == targetChar3) {
                mapBack3 = (int)k;
                break;
            }
        }
        int outBack3 = (mapBack3 - pos3 + ring3 + 26) % 26;
        if (showProcess) cout << "Обратно 3: " << setw(2) << stepBack3 << " " << targetChar3 << " "
                              << mapBack3 << " " << outBack3 << endl;

        char finalChar = alphabetUPPER[outBack3];
        resultEncr += finalChar;

        if (showProcess) cout << "Результат: " << finalChar << endl;
    }

    if (showProcess) {
        cout << "\n=== ИТОГ ===" << endl;
        cout << "Исходная строка: " << cipherText << endl;
        cout << "Выходная строка: " << resultEncr << endl;
    }

    return resultEncr;
}
