#ifndef ENIGMA_CIPHER_H
#define ENIGMA_CIPHER_H

#include <string>
#include <vector>
#include <utility>

std::string enigmaCipherEncr(const std::string& inputStr, const std::string& alphabetUPPER,
                             std::vector<std::pair<int32_t,char>>& nonPrintableSymbols,
                             std::vector<int> ROTORSbegin,
                             const std::string& ROTOR1UPPER,
                             const std::string& ROTOR2UPPER,
                             const std::string& ROTOR3UPPER,
                             const std::string& REFLBUPPER,
                             int ring1, int ring2, int ring3,
                             bool showProcess = true);

std::string enigmaCipherDecr(const std::string& cipherText, const std::string& alphabetUPPER,
                             std::vector<int> ROTORSbegin,
                             const std::string& ROTOR1UPPER,
                             const std::string& ROTOR2UPPER,
                             const std::string& ROTOR3UPPER,
                             const std::string& REFLBUPPER,
                             int ring1, int ring2, int ring3,
                             bool showProcess = true);

#endif
