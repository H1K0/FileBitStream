#include "../ifbstream.hpp"

ifbstream::~ifbstream() {
    _fstream.close();
}
