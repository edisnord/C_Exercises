cmake_minimum_required(VERSION 3.21)
project(Test C)

set(CMAKE_C_STANDARD 99)

add_executable(Test "Bit-Related exercises/setbits.c" "Bit-Related exercises/setbits.h" main.c "Bit-Related exercises/invert.c"
        "Bit-Related exercises/invert.h" "Bit-Related exercises/basic_operations_bit.h" "Bit-Related exercises/basic_operations_bit.c"
        "Bit-Related exercises/rightRot.c" "Bit-Related exercises/rightRot.h" "Bit-Related exercises/bitCount.c"
        "Bit-Related exercises/bitCount.h" "Char-related exercises/lower.c" "Char-related exercises/lower.h" "chapter_3.h"
        "chapter_3.c" chapter4.c chapter4.h "chapter4_calculator.c" "chapter4_calculator.h" main.h chapter5.c chapter5.h glad.h chapter6.c chapter6.h)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

target_link_libraries(Test m glfw)