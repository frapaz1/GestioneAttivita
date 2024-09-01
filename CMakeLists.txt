cmake_minimum_required(VERSION 3.10)
project(GestioneAttivita)

set(CMAKE_CXX_STANDARD 17)

add_executable(GestioneAttivita main.cpp attivita.cpp)

cmake_minimum_required(VERSION 3.10)
project(GestioneAttivita)

set(CMAKE_CXX_STANDARD 17)

# Aggiungi Google Test
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
# Imposta GTest come parte del build
FetchContent_MakeAvailable(googletest)
enable_testing()

# Aggiungi l'eseguibile principale
add_executable(GestioneAttivitaApp main.cpp attivita.cpp)
# Rinomina l'eseguibile principale in modo univoco

# Aggiungi un eseguibile per i test
add_executable(GestioneAttivitaTests test.cpp attivita.cpp)
# Rinomina l'eseguibile dei test in modo univoco
target_link_libraries(GestioneAttivitaTests gtest_main)

include(GoogleTest)
gtest_discover_tests(GestioneAttivitaTests)
