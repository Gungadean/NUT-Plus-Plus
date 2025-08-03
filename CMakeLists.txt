cmake_minimum_required(VERSION 3.31)
project(nut-plus-plus VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Find NUT using the standard pkg-config module ---
# This is the modern, cross-platform way to find libraries.
find_package(PkgConfig REQUIRED)
pkg_check_modules(UPS REQUIRED IMPORTED_TARGET libupsclient)

if(NOT NUT_FOUND)
    message(FATAL_ERROR "pkg-config could not find the NUT client library. Did you run 'sudo apt-get install libnut-dev'?")
endif()
message(STATUS "Found NUT and created imported target 'PkgConfig::NUT'")


# --- Define your library target ---
add_library(nut-plus-plus STATIC
        src/Connection.cpp
        src/UPS.cpp
        src/exceptions/NUTException.h
        src/exceptions/ConnectionException.h
        src/exceptions/CommandException.h
        src/exceptions/AuthenticationException.h
        src/exceptions/UPSException.h
        src/exceptions/ClientException.h
        src/exceptions/VariableException.h
)

# --- Link your library against the special NUT target ---
# This one command handles BOTH include directories AND library linking.
target_link_libraries(nut-plus-plus PUBLIC PkgConfig::UPS)


# --- Define your executable for testing ---
add_executable(Tester main.cpp)

# --- Link the executable against your library ---
target_link_libraries(Tester PRIVATE nut-plus-plus PkgConfig::UPS)