#include "../ofbstream.hpp"

ofbstream::~ofbstream() {
    _buffer[0] <<= _bitpos;
    _fstream.write(_buffer, 1);
    _fstream.close();
}
