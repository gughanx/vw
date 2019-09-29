cmake_minimum_required (VERSION 3.13.4)
project(vw)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_CXX_COMPILER "g++-9")
set(CMAKE_STANDARD 20)
set(CMAKE_CXX_FLAGS "-fconcepts")

# Install Directories
set(INSTALL_LIB_DIR ${CMAKE_INSTALL_PREFIX}/lib)
set(INSTALL_BIN_DIR ${CMAKE_INSTALL_PREFIX}/bin)
set(INSTALL_INCLUDE_DIR ${CMAKE_INSTALL_PREFIX}/include)
if(WIN32 AND NOT CYGWIN)
    set(INSTALL_CMAKE_DIR ${CMAKE_INSTALL_PREFIX}/CMake)
else()
    set(INSTALL_CMAKE_DIR ${CMAKE_INSTALL_PREFIX}/lib/cmake/${PROJECT_NAME})
endif()

# Find dependencies
find_package(GTest)

# Macro to add a library
macro(vw_add_lib LIB_NAME)
    file(GLOB DEFAULT_LIB_SOURCES *.cpp)
    file(GLOB DEFAULT_LIB_HEADERS *.hpp)
    add_library(${LIB_NAME} ${DEFAULT_LIB_SOURCES} ${DEFAULT_LIB_HEADERS})
    set_target_properties(${LIB_NAME} PROPERTIES LINKER_LANGUAGE CXX)
endmacro()

# Macro to add an unit test
macro(vw_add_test TEST_NAME)
    include_directories(${GTEST_INCLUDE_DIRS})
    file(GLOB DEFAULT_UNIT_TEST_SOURCES *Tests.cpp)
    file(GLOB DEFAULT_UNIT_TEST_HEADERS *Tests.hpp)
    add_executable(${TEST_NAME} ${CMAKE_SOURCE_DIR}/GTest/Main.cpp
                   ${DEFAULT_UNIT_TEST_SOURCES} ${DEFAULT_UNIT_TEST_HEADERS})
    target_link_libraries(${TEST_NAME} ${GTEST_LIBRARIES} pthread ${LIBS})
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME} "--gtest_output=xml")
    set_property(TARGET ${TEST_NAME} PROPERTY CXX_STANDARD 20)
endmacro()

# Add vw code
add_subdirectory(Core)
add_subdirectory(Math)
