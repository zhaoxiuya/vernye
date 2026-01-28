cmake_minimum_required(VERSION 3.11)

project(
  Vernye
  VERSION 0.0.0
  DESCRIPTION "lambda calculus beta reduction calculator"
  LANGUAGES C
)

add_executable(
    program
    test/main.c
    src/beta.c
    src/node.c
    src/state.c
    src/zxl.c
)

target_include_directories(program PUBLIC include)