cmake_minimum_required(VERSION 3.12)
project(Aegis2)

add_compile_definitions(AEGIS_DLL_BUILD)

add_library(Aegis2 SHARED "")
include(sourcelist.cmake)

