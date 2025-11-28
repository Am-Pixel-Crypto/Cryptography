
##
### Author: Haytham Ashraf

CMAKE_MINIMUM_REQUIRED(VERSION 4.1)

PROJECT(Cryptography VERSION 1.0 LANGUAGES CXX)

# unit files for the main program
SET(SRC LA.cpp io.cpp crypto.cpp)

ADD_EXECUTABLE(crypto)
TARGET_SOURCES(crypto PRIVATE main.cpp ${SRC})

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    # message(STATUS "Debug build")
    TARGET_COMPILE_DEFINITIONS(crypto PUBLIC _DEBUG)
else()
    # message(STATUS "Debug Release")
    # TARGET_COMPILE_DEFINITIONS(crypto PUBLIC _RELEASE)
endif()