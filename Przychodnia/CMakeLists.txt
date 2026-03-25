cmake_minimum_required(VERSION 4.0)
project(Przychodnia C)

set(CMAKE_C_STANDARD 11)

add_executable(Przychodnia main.c lekarz.c pacjent.c wizyta.c file_man.c)
