#include "fbstream.h"

ifbstream::ifbstream(std::string path) {
	_fstream.open(path, std::ifstream::in | std::ifstream::binary);
	_fstream.read(_buffer, 1);
}
unsigned long long int ifbstream::read(unsigned char len) {
	if (len > 64) {
		throw std::length_error("Too big length");
	}
	unsigned long long int out = 0;
	if (_bitpos < len) {
		out |= _buffer[0] & ((1 << _bitpos) - 1);
		len -= _bitpos;
		_fstream.read(_buffer, 1);
		_bitpos = 8;
	}
	while (len > 8) {
		out = out << 8 | _buffer[0];
		len -= 8;
		_fstream.read(_buffer, 1);
	}
	out = out << len | _buffer[0] >> _bitpos - len & ((1 << len) - 1);
	if ((_bitpos -= len) == 0) {
		_fstream.read(_buffer, 1);
		_bitpos = 8;
	}
	return out;
}
