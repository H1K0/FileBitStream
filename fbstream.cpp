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
void ifbstream::rewind() {
	_fstream.clear();
	_fstream.seekg(0);
	_bitpos = 8;
	_buffer[1] = { 0 };
}
void ifbstream::close() {
	_fstream.close();
}

ofbstream::ofbstream(std::string path) {
	_fstream.open(path, std::ifstream::binary);
}
ofbstream::~ofbstream() {
	_buffer[0] <<= _bitpos;
	_fstream.write(_buffer, 1);
	_fstream.close();
}
void ofbstream::write(unsigned long long int data, unsigned char len) {
	if (len > 64) {
		throw std::length_error("Too big length");
	}
	data &= (1 << len) - 1;
	if (_bitpos < len) {
		_buffer[0] = _buffer[0] << _bitpos | data >> (len -= _bitpos);
		_fstream.write(_buffer, 1);
		_bitpos = 8;
	}
	while (len > 8) {
		_buffer[0] = data >> (len -= 8);
		_fstream.write(_buffer, 1);
	}
	if (len) {
		_buffer[0] = data & (1 << len) - 1;
		_bitpos -= len;
	}
}
void ofbstream::close() {
	_buffer[0] <<= _bitpos;
	_fstream.write(_buffer, 1);
	_fstream.close();
}
