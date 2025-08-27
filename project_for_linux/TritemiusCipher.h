#ifndef TRITEMIUS_CIPHER_H
#define TRITEMIUS_CIPHER_H

#include <string>
#include <vector>
#include <cstdint>

int64_t kFunction(int x, const std::vector<int>& coeffs);

uint32_t tritemiusCipher(uint32_t code, uint32_t position, int64_t shift);

uint32_t reverseTritemius(uint32_t code, uint32_t position, int64_t shift);

std::string encryptText(const std::string& text, const std::vector<int>& coeffs, bool showProcess = true);

std::string decryptText(const std::string& text, const std::vector<int>& coeffs, bool showProcess = true);

std::vector<uint8_t> encryptBytes(const std::vector<uint8_t>& data, const std::vector<int>& coeffs, bool showProcess = false);

std::vector<uint8_t> decryptBytes(const std::vector<uint8_t>& data, const std::vector<int>& coeffs, bool showProcess = false);

#endif
