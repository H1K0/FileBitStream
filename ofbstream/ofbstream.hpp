#include <fstream>
#include <string>

class ofbstream {
private:
    std::ofstream _fstream;
    unsigned long long int _bitpos = 8;
    char _buffer[1] = { 0 };

public:
    ofbstream(std::string path);
    ofbstream(std::wstring path);
    ~ofbstream();
    void write(unsigned long long int data, unsigned char blocksize);
    void close();
};
