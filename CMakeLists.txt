cmake_minimum_required(VERSION 3.10)
project(AttivitaLog)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${PROJECT_SOURCE_DIR})

set(SOURCES
        attivita.cpp
        lista_attivita.cpp
        main.cpp
)

add_executable(attivita_log ${SOURCES})

list(REMOVE_ITEM SOURCES main.cpp)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

set(TEST_SOURCES
        test/test.cpp
)

add_executable(attivita_log_test ${TEST_SOURCES} ${SOURCES})

target_link_libraries(attivita_log_test gtest gtest_main)

add_test(NAME attivita_log_test COMMAND attivita_log_test)
