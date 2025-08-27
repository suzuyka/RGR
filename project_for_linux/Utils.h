#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <cstdint>

uint8_t mod256(long long x);

std::vector<uint8_t> stringToBytes(const std::string& s);
std::string bytesToString(const std::vector<uint8_t>& data);

std::vector<uint8_t> ReadFile(const std::string& filename);
bool WriteFile(const std::string& filename, const std::vector<uint8_t>& data);

#endif
