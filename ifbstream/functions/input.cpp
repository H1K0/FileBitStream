#include "../ifbstream.hpp"

unsigned long long int ifbstream::read(unsigned char blocksize) {
    if (blocksize > 64) {
        throw std::overflow_error("Too big length");
    }
    if (_fstream.eof()) {
        throw std::out_of_range("Length out of range");
    }
    unsigned long long int out = 0;
    if (_bitpos < blocksize) {
        out |= _buffer[0] & ((1 << _bitpos) - 1);
        blocksize -= _bitpos;
        _fstream.read(_buffer, 1);
        _bitpos = 8;
    }
    if (_fstream.eof() && blocksize) {
        throw std::out_of_range("Length out of range");
    }
    while (blocksize > 8) {
        if (_fstream.eof()) {
            throw std::out_of_range("Length out of range");
        }
        out = out << 8 | _buffer[0] & 0b11111111;
        blocksize -= 8;
        _fstream.read(_buffer, 1);
    }
    if (blocksize) {
        if (_fstream.eof()) {
            throw std::out_of_range("Length out of range");
        }
        out = out << blocksize | _buffer[0] >> _bitpos - blocksize & ((1 << blocksize) - 1);
        if ((_bitpos -= blocksize) == 0) {
            _fstream.read(_buffer, 1);
            _bitpos = 8;
        }
    }
    return out;
}
