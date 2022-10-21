cmake_minimum_required(VERSION 3.23)
project(fbstream)

set(CMAKE_CXX_STANDARD 14)

set(IFBSTREAM_SOURCE
        ifbstream/ifbstream.hpp
        ifbstream/constructors/constructors.cpp
        ifbstream/constructors/destructors.cpp
        ifbstream/functions/stream.cpp
        ifbstream/functions/position.cpp
        ifbstream/functions/input.cpp)
set(OFBSTREAM_SOURCE
        ofbstream/ofbstream.hpp
        ofbstream/constructors/constructors.cpp
        ofbstream/constructors/destructors.cpp
        ofbstream/functions/stream.cpp
        ofbstream/functions/position.cpp
        ofbstream/functions/output.cpp)

add_library(fbstream SHARED fbstream.hpp ${IFBSTREAM_SOURCE} ${OFBSTREAM_SOURCE})
