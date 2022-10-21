#include "../ifbstream.hpp"

void ifbstream::rewind() {
    _fstream.clear();
    _fstream.seekg(0);
    _bitpos = 8;
    _buffer[1] = { 0 };
}
