#include "../ofbstream.hpp"

ofbstream::ofbstream(std::string path) {
    _fstream.open(path, std::ifstream::binary);
    if (!_fstream) {
        throw std::runtime_error("Error opening file");
    }
}
ofbstream::ofbstream(std::wstring path) {
    _fstream.open(path, std::ifstream::binary);
    if (!_fstream) {
        throw std::runtime_error("Error opening file");
    }
}
