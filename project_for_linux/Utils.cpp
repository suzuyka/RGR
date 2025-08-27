#include "Utils.h"
#include <fstream>
#include <iostream>
using namespace std;

uint8_t mod256(long long x) {
    x %= 256;
    if (x < 0) x += 256;
    return static_cast<uint8_t>(x);
}

vector<uint8_t> stringToBytes(const string& s) {
    return vector<uint8_t>(s.begin(), s.end());
}

string bytesToString(const vector<uint8_t>& data) {
    return string(data.begin(), data.end());
}

vector<uint8_t> ReadFile(const string& filename) {
    ifstream file(filename, ios::binary | ios::ate);
    if (!file) { cerr << "Ошибка открытия файла: " << filename << endl; return {}; }

    size_t fileSize = file.tellg();
    file.seekg(0, ios::beg);

    vector<uint8_t> buffer(fileSize);
    if (!file.read(reinterpret_cast<char*>(buffer.data()), fileSize)) {
        cerr << "Ошибка чтения файла: " << filename << endl;
        return {};
    }
    return buffer;
}

bool WriteFile(const string& filename, const vector<uint8_t>& data) {
    ofstream file(filename, ios::binary);
    if (!file) { cerr << "Ошибка создания файла: " << filename << endl; return false; }
    if (!file.write(reinterpret_cast<const char*>(data.data()), data.size())) {
        cerr << "Ошибка записи файла: " << filename << endl; return false;
    }
    return true;
}
