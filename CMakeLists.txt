##
##
### Author: Haytham Ashraf

CMAKE_MINIMUM_REQUIRED(VERSION 4.1)

PROJECT(Cryptography VERSION 1.0 LANGUAGES CXX)

OPTION(WITH_GUI "Generate GUI Application" ON)

# unit files for the main program
SET(SOURCES
    LA.cpp
    io.cpp
    crypto.cpp)

ADD_LIBRARY(core OBJECT)
TARGET_SOURCES(core PRIVATE ${SOURCES})

ADD_EXECUTABLE(crypto)
TARGET_SOURCES(crypto PRIVATE main.cpp)
TARGET_LINK_LIBRARIES(crypto PRIVATE core)

IF(CMAKE_BUILD_TYPE STREQUAL "Debug")
    # message(STATUS "Debug build")
    TARGET_COMPILE_DEFINITIONS(crypto PUBLIC _DEBUG)
ENDIF()

IF(WITH_GUI)
    FIND_PACKAGE(wxWidgets QUIET)

    IF(NOT wxWidgets_FOUND)
        MESSAGE(WARNING "wxWidgets could be found\nIgnoring GUI Application")
    ELSE()
        MESSAGE(STATUS "Generating GUI Application")
        ADD_EXECUTABLE(crypto-gui)
        TARGET_SOURCES(crypto-gui PRIVATE main-gui.cpp ${SOURCES})

        TARGET_LINK_LIBRARIES(crypto-gui PRIVATE ${wxWidgets_LIBRARIES})
        TARGET_INCLUDE_DIRECTORIES(crypto-gui PRIVATE ${wxWidgets_INCLUDE_DIRS})
        TARGET_COMPILE_DEFINITIONS(crypto-gui PRIVATE "${wxWidgets_DEFINITIONS}")
        TARGET_LINK_LIBRARIES(crypto PRIVATE core)

        IF(CMAKE_BUILD_TYPE STREQUAL "Debug")
            # building as debug
            TARGET_COMPILE_DEFINITIONS(crypto-gui PUBLIC "_DEBUG")
        ENDIF()
    ENDIF()
ENDIF()