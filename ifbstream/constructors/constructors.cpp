#include "../ifbstream.hpp"

ifbstream::ifbstream(std::string path) {
    _fstream.open(path, std::ifstream::binary);
    if (!_fstream) {
        throw std::runtime_error("Error opening file");
    }
    _fstream.read(_buffer, 1);
}
ifbstream::ifbstream(std::wstring path) {
    _fstream.open(path, std::ifstream::binary);
    if (!_fstream) {
        throw std::runtime_error("Error opening file");
    }
    _fstream.read(_buffer, 1);
}
