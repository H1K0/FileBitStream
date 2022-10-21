#include "../ofbstream.hpp"

void ofbstream::write(unsigned long long int data, unsigned char blocksize) {
    if (blocksize > 64) {
        throw std::overflow_error("Too big length");
    }
    data &= (1 << blocksize) - 1;
    if (_bitpos < blocksize) {
        _buffer[0] = _buffer[0] << _bitpos | data >> (blocksize -= _bitpos);
        _fstream.write(_buffer, 1);
        _bitpos = 8;
    }
    while (blocksize > 8) {
        _buffer[0] = data >> (blocksize -= 8);
        _fstream.write(_buffer, 1);
    }
    if (blocksize) {
        _buffer[0] = _buffer[0] << blocksize | data & (1 << blocksize) - 1;
        _bitpos -= blocksize;
        if (!_bitpos) {
            _fstream.write(_buffer, 1);
            _bitpos = 8;
        }
    }
}
