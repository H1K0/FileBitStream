#pragma once

#include <fstream>
#include <string>

class ifbstream {
private:
	std::ifstream _fstream;
	unsigned long long int _bitpos = 8;
	char _buffer[1] = { 0 };

public:
	ifbstream(std::string path);
	~ifbstream();
	unsigned long long int read(unsigned char len);
	void rewind();
	void close();
};
