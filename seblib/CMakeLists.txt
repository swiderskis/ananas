cmake_minimum_required(VERSION 3.25)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(
  seblib
  src/seblib.cpp
)

target_include_directories(
  seblib
  PUBLIC
  include/
)

target_compile_options(
  seblib
  PRIVATE
  -Wall
  -Wextra
  -Werror
  -Wpedantic
  $<$<CXX_COMPILER_ID:GNU>:-freflection>
)
