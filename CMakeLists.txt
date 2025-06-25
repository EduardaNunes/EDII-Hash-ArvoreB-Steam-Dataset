cmake_minimum_required(VERSION 3.14)

# Altere o nome do projeto caso julgue necessário
project(Trabalho)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Adiciona a pasta src aos caminhos de include
include_directories(${CMAKE_SOURCE_DIR}/src)

# Enable testing
include(CTest)
enable_testing()

# incluir os demais comandos cmake abaixo...

add_executable(meu_programa
    src/main.cpp
    src/Menu/menu.cpp
    src/Hash/hash.cpp
)

add_executable(tests
    src/tests/test_hash.cpp
     src/Hash/hash.cpp
)

target_include_directories(tests PRIVATE src)
add_test(NAME PlayerHashTests COMMAND tests)

set_target_properties(meu_programa PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
  RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}
  RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}
)
