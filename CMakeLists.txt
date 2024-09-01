cmake_minimum_required(VERSION 3.10)
project(GestioneAttivita)

set(CMAKE_CXX_STANDARD 17)

add_executable(GestioneAttivita main.cpp attivita.cpp)

cmake_minimum_required(VERSION 3.10)
project(GestioneAttivita)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)
enable_testing()

add_executable(GestioneAttivitaApp main.cpp attivita.cpp)

add_executable(GestioneAttivitaTests test.cpp attivita.cpp)

target_link_libraries(GestioneAttivitaTests gtest_main)

include(GoogleTest)
gtest_discover_tests(GestioneAttivitaTests)
