#include "fbstream.h"

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
ifbstream::~ifbstream() {
	_fstream.close();
}
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
ofbstream::~ofbstream() {
	_buffer[0] <<= _bitpos;
	_fstream.write(_buffer, 1);
	_fstream.close();
}
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
void ofbstream::close() {
	if (_bitpos != 8) {
		_buffer[0] <<= _bitpos;
		_fstream.write(_buffer, 1);
	}
	_fstream.close();
}
