cmake_minimum_required(VERSION 3.25)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  test
  src/game.cpp
  src/search.cpp
  src/square.cpp
)

target_link_libraries(
  test
  PRIVATE
  GTest::gtest_main
  chesslib
  seblib
)

target_compile_options(
  test
  PRIVATE
  -Wall
  -Wextra
  -Werror
  -Wpedantic
  $<$<CXX_COMPILER_ID:GNU>:-freflection>
)

include(GoogleTest)
gtest_discover_tests(test)
