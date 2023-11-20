cmake_minimum_required(VERSION 3.26)
project(catlib-unam C)

set(CMAKE_C_STANDARD 17)

add_executable(catlib-unam main.c)

# Ejecutar como administrador
configure_file(${CMAKE_SOURCE_DIR}/books.txt ${CMAKE_CURRENT_BINARY_DIR}/books.txt USE_SOURCE_PERMISSIONS)
configure_file(${CMAKE_SOURCE_DIR}/users.txt ${CMAKE_CURRENT_BINARY_DIR}/users.txt USE_SOURCE_PERMISSIONS)
configure_file(${CMAKE_SOURCE_DIR}/records.txt ${CMAKE_CURRENT_BINARY_DIR}/records.txt USE_SOURCE_PERMISSIONS)