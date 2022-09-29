#include "fbstream.h"

ifbstream::ifbstream(std::string path) {
	_fstream.open(path, std::ifstream::binary);
	_fstream.read(_buffer, 1);
}
ifbstream::~ifbstream() {
	_fstream.close();
}
unsigned long long int ifbstream::read(unsigned char len) {
	if (len > 64) {
		throw std::length_error("Too big length");
	}
	if (_fstream.eof()) {
		throw std::out_of_range("Length out of range");
	}
	unsigned long long int out = 0;
	if (_bitpos < len) {
		out |= _buffer[0] & ((1 << _bitpos) - 1);
		len -= _bitpos;
		_fstream.read(_buffer, 1);
		_bitpos = 8;
	}
	if (_fstream.eof() && len) {
		throw std::out_of_range("Length out of range");
	}
	while (len > 8) {
		if (_fstream.eof()) {
			throw std::out_of_range("Length out of range");
		}
		out = out << 8 | _buffer[0];
		len -= 8;
		_fstream.read(_buffer, 1);
	}
	if (len) {
		if (_fstream.eof()) {
			throw std::out_of_range("Length out of range");
		}
	out = out << len | _buffer[0] >> _bitpos - len & ((1 << len) - 1);
	if ((_bitpos -= len) == 0) {
		_fstream.read(_buffer, 1);
		_bitpos = 8;
	}
	}
	return out;
}
void ifbstream::close() {
	_fstream.close();
}
