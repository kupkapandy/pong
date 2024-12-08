cmake_minimum_required(VERSION 3.10)
project(game VERSION 1.0)

set(CMAKE_C_COMPILER "clang")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

add_executable(main src/main.c)

target_link_libraries(main SDL2 SDL2_image)
target_compile_options(main PRIVATE
    -Wall
    -std=c2x
    -O2
    -g
    -Wextra
    -Wpedantic
    -Wfloat-equal
    -Wstrict-aliasing
    -Wswitch-default
    -Wformat=2
    -Wno-newline-eof
    -Wno-unused-parameter
    -Wno-strict-prototypes
    -Wno-fixed-enum-extension
    -Wno-int-to-void-pointer-cast
    -Wno-gnu-statement-expression
    -Wno-gnu-compound-literal-initializer
    -Wno-gnu-zero-variadic-macro-arguments
    -Wno-gnu-empty-struct
    -Wno-gnu-auto-type
    -Wno-gnu-empty-initializer
    -Wno-gnu-pointer-arith
    -Wno-c99-extensions
    -Wno-c11-extensions
)
