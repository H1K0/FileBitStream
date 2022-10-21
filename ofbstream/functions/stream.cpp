#include "../ofbstream.hpp"

void ofbstream::close() {
    if (_bitpos != 8) {
        _buffer[0] <<= _bitpos;
        _fstream.write(_buffer, 1);
    }
    _fstream.close();
}
