#ifndef SUZUYA_CIPHER_H
#define SUZUYA_CIPHER_H

#include <string>
#include <vector>
#include <cstdint>


std::vector<uint8_t> suzuyaEncrypt(const std::vector<uint8_t>& data, int shift, long long addNumber, bool showProcess = false);
std::vector<uint8_t> suzuyaDecrypt(const std::vector<uint8_t>& data, int shift, long long addNumber, bool showProcess = false);


std::string encryptText(const std::string& text, int shift, long long addNumber, bool showProcess = false);
std::string decryptText(const std::string& encrypted, int shift, long long addNumber, bool showProcess = false);

// Работа с файлами
std::vector<uint8_t> ReadFile(const std::string& filename);
bool WriteFile(const std::string& filename, const std::vector<uint8_t>& data);

#endif
